/*
 * Track.cpp
 *
 * \date 8 avr. 2013, 15:16:34
 *  \author cec
 */

#include "Track.hpp"
#include "Leg.hpp"
#include <sstream>
#include <cmath>


#include "test_macros.hpp"
class Track::TrackImpl
{
    public:
        TrackImpl(const std::vector<LatitudeLongitude>& waypoints_//!< List of points composing the track (at least two), longitude & latitude given in decimal degrees on the WGS84
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
            bool previous_point_at_90_deg_latitude = false;
            bool previous_point_at_minus_90_deg_latitude = false;
            distance_from_start_to_begining_of_leg.push_back(0);
            for (size_t i = 0 ; i < nb_of_legs-1 ; ++i)
            {
                legs.push_back(Leg(waypoints.at(i),waypoints.at(i+1)));
                check_poles(waypoints.at(i).lat, waypoints.at(i+1).lat, previous_point_at_90_deg_latitude, previous_point_at_minus_90_deg_latitude);
                const double d = legs.back().length();
                length += d;
                distance_from_start_to_begining_of_leg.push_back(distance_from_start_to_begining_of_leg.back()+d);
            }
            legs.push_back(Leg(waypoints.at(nb_of_legs-1),waypoints.at(nb_of_legs)));
            length += legs.back().length();
        }

        void check_poles(const double P_lat, const double Q_lat, bool& previous_point_at_90_deg_latitude, bool& previous_point_at_minus_90_deg_latitude) const
        {
            if ((previous_point_at_90_deg_latitude || (Q_lat == 90)) && (P_lat == 90))
            {
                THROW(__PRETTY_FUNCTION__, TrackException, "Two consecutive points are at 90 deg latitude");
            }
            if ((previous_point_at_minus_90_deg_latitude || (Q_lat == -90)) && (P_lat == -90))
            {
                THROW(__PRETTY_FUNCTION__, TrackException, "Two consecutive points are at -90 deg latitude");
            }
            previous_point_at_minus_90_deg_latitude = (P_lat == -90);
            previous_point_at_90_deg_latitude = (P_lat == 90);
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
        std::vector<LatitudeLongitude> waypoints;

    private:
        TrackImpl();
};

Track::Track(const std::vector<LatitudeLongitude>& waypoints //!< List of points composing the track (at least two), longitude & latitude given in decimal degrees on the WGS84
             ) : pimpl(new Track::TrackImpl(waypoints))
{

}

/** \author cec
 *  \date 11 avr. 2013, 15:26:32
 *  \brief Retrieve the waypoints used to construct the track
 *  \returns List of waypoints
 *  \snippet /unit_tests/src/TrackTest.cpp TrackTest get_waypoints_example
*/
std::vector<LatitudeLongitude> Track::get_all_waypoints() const
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
    const std::vector<LatitudeLongitude> waypoints = pimpl->waypoints;
    std::vector<LatitudeLongitude> waypoints_on_first_subtrack, waypoints_on_second_subtrack;
    const size_t n = waypoints.size();
    const LatitudeLongitude common_point_to_two_subtracks = find_waypoint_on_track(distance_from_start_of_track);
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
 *  \date 27 mai 2013, 15:01:34
 *  \brief
 *  \returns
 *  \snippet geometry/unit_tests/src/TrackTest.cpp TrackTest Track::azimuth_at_example
*/
Angle Track::azimuth_at(const double& distance_from_point1) const
{
    const size_t idx = find_leg_index(distance_from_point1);
    const double d = distance_from_point1-pimpl->distance_from_start_to_begining_of_leg.at(idx);
    return pimpl->legs.at(idx).azimuth_at(d);
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

Track::~Track()
{

}

/** \author cec
 *  \date 8 avr. 2013, 18:06:31
 *  \brief Find a waypoint on the track, at a given distance from the first point
 *  \returns Longitude & latitude of point at given distance from start of track
 *  \snippet /unit_tests/src/TrackTest.cpp TrackTest find_waypoint_on_track_example
 */
LatitudeLongitude Track::find_waypoint_on_track(const double& distance //!< Distance (measured on the track) from first waypoint (in meters)
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

/** \author cec
 *  \date 12 avr. 2013, 16:27:37
 *  \brief Test two tracks for equality
 *  \returns true if the two tracks are equal (within 1 mm), false otherwise
*/
bool Track::operator==(const Track& rhs) const
{
    const double tolerance = 1e-3;
    const auto waypoints_track_1 = pimpl->waypoints;
    const auto waypoints_track_2 = rhs.get_all_waypoints();
    const size_t n = waypoints_track_1.size();
    if (waypoints_track_2.size() != n) return false;
    for (size_t i = 0 ; i < n ; ++i)
    {
        const double lon1 = waypoints_track_1.at(i).lon;
        const double lat1 = waypoints_track_1.at(i).lat;
        const double lon2 = waypoints_track_2.at(i).lon;
        const double lat2 = waypoints_track_2.at(i).lat;
        if (fabs(lon1-lon2)>tolerance) return false;
        if (fabs(lat1-lat2)>tolerance) return false;
    }
    return true;
}

/** \author cec
 *  \date 12 avr. 2013, 16:27:37
 *  \brief Test two tracks for equality
 *  \returns false if the two tracks are equal (within 1 mm), true otherwise
*/
bool Track::operator!=(const Track& rhs) const
{
    return not(operator==(rhs));
}

/** \author cec
 *  \date 27 mai 2013, 17:07:35
 *  \brief Projects a point on a geodesic
 *  \returns
 *  \snippet /unit_tests/src/TrackTest.cpp TrackTest Track::find_closest_point_to_example
*/
std::pair<LatitudeLongitude, size_t> Track::find_closest_point_to(const LatitudeLongitude& point) const
{
    LatitudeLongitude nearest_point = pimpl->waypoints.front();
    double smallest_distance = 1e3*pimpl->length;
    size_t idx = 0;
    for (auto that_leg = pimpl->legs.begin() ; that_leg != pimpl->legs.end() ; ++that_leg)
    {
        LatitudeLongitude p = that_leg->find_closest_point_to(point);
        const double d = Leg(p,point).length();
        if (d<smallest_distance)
        {
            nearest_point = p;
            smallest_distance = d;
            idx = that_leg-pimpl->legs.begin();
        }
    }
    return std::make_pair(nearest_point,idx);
}

/** \author cec
 *  \date 28 mai 2013, 10:18:13
 *  \brief
 *  \returns
 *  \snippet /unit_tests/src/TrackTest.cpp TrackTest Track::distance_from_beginning_of_track_to_closest_point_example
*/
double Track::distance_from_beginning_of_track_to_closest_point(const LatitudeLongitude& point) const
{
    const std::pair<LatitudeLongitude,size_t> nearest_point = find_closest_point_to(point);
    const double pos = get_waypoint_position_on_track(nearest_point.second);
    return pos + Leg(pimpl->waypoints.at(nearest_point.second),nearest_point.first).length();
}
