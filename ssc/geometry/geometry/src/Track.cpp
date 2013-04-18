/*
 * Track.cpp
 *
 * \date 8 avr. 2013, 15:16:34
 *  \author cec
 */

#include "Track.hpp"
#include "Leg.hpp"
#include <sstream>

class Track::TrackImpl
{
    public:
        TrackImpl(const std::vector<LongitudeLatitude>& waypoints_//!< List of points composing the track (at least two), longitude & latitude given in decimal degrees on the WGS84
                     ) :
        distance_from_start_to_begining_of_leg(std::vector<double>()),
        legs(std::vector<Leg>()),
        length(0),
        nb_of_legs(waypoints_.size()-1),
        waypoints(waypoints_)
        {
            if (waypoints.size() < 2)
            {
                THROW("Track::Track(const std::vector<LongitudeLatitude>&)", TrackException, "Track should contain at least two waypoints");
            }
            distance_from_start_to_begining_of_leg.push_back(0);
            for (size_t i = 0 ; i < nb_of_legs-1 ; ++i)
            {
                legs.push_back(Leg(waypoints.at(i),waypoints.at(i+1)));
                const double d = legs.back().length();
                length += d;
                distance_from_start_to_begining_of_leg.push_back(distance_from_start_to_begining_of_leg.back()+d);
            }
            legs.push_back(Leg(waypoints.at(nb_of_legs-1),waypoints.at(nb_of_legs)));
            length += legs.back().length();
        }

        size_t find_leg_index(const double& distance) const
        {
            for (size_t i = 1 ; i < nb_of_legs ; ++i)
            {
                if (distance<=distance_from_start_to_begining_of_leg.at(i)) return i-1;
            }
            return nb_of_legs-1;
        }

        std::vector<double> distance_from_start_to_begining_of_leg;
        std::vector<Leg> legs;
        double length;
        size_t nb_of_legs;
        std::vector<LongitudeLatitude> waypoints;

    private:
        TrackImpl();
};

Track::Track(const std::vector<LongitudeLatitude>& waypoints //!< List of points composing the track (at least two), longitude & latitude given in decimal degrees on the WGS84
             ) : pimpl(new Track::TrackImpl(waypoints))
{

}

/** \author cec
 *  \date 11 avr. 2013, 15:26:32
 *  \brief Retrieve the waypoints used to construct the track
 *  \returns List of waypoints
 *  \snippet /unit_tests/src/TrackTest.cpp TrackTest get_waypoints_example
*/
std::vector<LongitudeLatitude> Track::get_all_waypoints() const
{
    return pimpl->waypoints;
}

/** \author cec
 *  \date 12 avr. 2013, 14:31:24
 *  \brief Separates a track in two subtracks of length d and L-d where L is the length of the original track & d the parameter of this method
 *  \returns Pair of tracks
 *  \snippet /unit_tests/src/TrackTest.cpp TrackTest split_at_example
*/
std::pair<Track,Track> Track::split_at(const double& distance_from_start_of_track) const
{
    if ((distance_from_start_of_track<=0) || (distance_from_start_of_track>=length()))
    {
        std::stringstream ss;
        ss << "Invalid split length: split distance should be within [0,"
           << length() << ", but asked to split at " << distance_from_start_of_track;
        THROW("Track::split_at(const double&)", TrackException, ss.str());
    }
    const std::vector<LongitudeLatitude> waypoints = pimpl->waypoints;
    std::vector<LongitudeLatitude> waypoints_on_first_subtrack, waypoints_on_second_subtrack;
    const size_t n = waypoints.size();
    const LongitudeLatitude common_point_to_two_subtracks = find_waypoint_on_track(distance_from_start_of_track);
    waypoints_on_second_subtrack.push_back(common_point_to_two_subtracks);
    for (size_t i = 0 ; i < (n-1) ; ++i)
    {
        const double distance_from_start_to_waypoint_i = pimpl->distance_from_start_to_begining_of_leg.at(i);
        if (distance_from_start_to_waypoint_i>distance_from_start_of_track)
        {
            waypoints_on_second_subtrack.push_back(waypoints.at(i));
        }
        else
        {
            waypoints_on_first_subtrack.push_back(waypoints.at(i));
        }
    }
    waypoints_on_first_subtrack.push_back(common_point_to_two_subtracks);
    waypoints_on_second_subtrack.push_back(waypoints.back());
    return std::make_pair(Track(waypoints_on_first_subtrack), Track(waypoints_on_second_subtrack));
}

/** \author cec
 *  \date 8 avr. 2013, 15:32:27
 *  \brief Computes the sum of the lengths of each segment taken on the WGS84 (geodesic arcs)
 *  \returns Length of the track (in meters)
 *  \snippet geometry/unit_tests/src/TrackTest.cpp TrackTest example
 *  \snippet geometry/unit_tests/src/TrackTest.cpp TrackTest expected output
 */
double Track::length() const
{
    return pimpl->length;
}

/** \author cec
 *  \date 8 avr. 2013, 18:06:31
 *  \brief Find a waypoint on the track, at a given distance from the first point
 *  \returns Longitude & latitude of point at given distance from start of track
 *  \snippet /unit_tests/src/TrackTest.cpp TrackTest find_waypoint_on_track_example
 */
LongitudeLatitude Track::find_waypoint_on_track(const double& distance //!< Distance (measured on the track) from first waypoint (in meters)
                                               ) const
{
    if (distance>length())
    {
        THROW("Track::find_waypoint_on_track(const double&)", TrackException, "Point is farther than the last point on track");
    }
    if (distance<0)
    {
        THROW("Track::find_waypoint_on_track(const double&)", TrackException, "received a negative distance");
    }
    const size_t idx = find_leg_index(distance);
    return pimpl->legs.at(idx).find_waypoint_at(distance-pimpl->distance_from_start_to_begining_of_leg.at(idx));
}

/** \author cec
 *  \date 8 avr. 2013, 18:08:44
 *  \brief When calling find_waypoint_on_track, we need to know the waypoints surrounding the target:
 *  \returns Index of point just before the point at 'distance' from first waypoint (start of track)
 *  \snippet /unit_tests/src/TrackTest.cpp TrackTest find_leg_index_example
 */
size_t Track::find_leg_index(const double& distance_from_start_of_track //!< Distance from first waypoint (in meters)
                             ) const
{
    if (distance_from_start_of_track<0)
    {
        THROW("Track::find_leg_index(const double&)", TrackException, "Distance from start of track can't be negative");
    }
    return pimpl->find_leg_index(distance_from_start_of_track);
}


/** \author cec
 *  \date 9 avr. 2013, 12:58:22
 *  \brief Distance (on track) of waypoint 'waypoint_idx' from the first waypoint
 *  \returns Distance from first waypoint (in meters)
 *  \snippet /unit_tests/src/TrackTest.cpp TrackTest distance_from_start_example
 */
double Track::get_waypoint_position_on_track(const size_t& waypoint_idx //!< Index of the waypoint of which we wish to calculate the position
                                  ) const
{
    if (waypoint_idx < pimpl->nb_of_legs) return pimpl->distance_from_start_to_begining_of_leg.at(waypoint_idx);
    return pimpl->length;
}
