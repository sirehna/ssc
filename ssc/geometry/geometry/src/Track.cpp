/*
 * Track.cpp
 *
 * \date 8 avr. 2013, 15:16:34
 *  \author cec
 */

#include "Track.hpp"
#include "Leg.hpp"

class Track::TrackImpl
{
    public:
        TrackImpl(const std::vector<LongitudeLatitude>& waypoints_,//!< List of points composing the track (at least two), longitude & latitude given in decimal degrees on the WGS84
                     const Date& departure_time_,                     //!< Time at the first point (POSIX time)
                     const Date& arrival_time_                        //!< Time at last point (greater than departure time) (POSIX time)
                     ) :
        departure_time(departure_time_),
        arrival_time(arrival_time_),
        distance_from_start_to_begining_of_leg(std::vector<double>()),
        legs(std::vector<Leg>()),
        length(0),
        nb_of_legs(waypoints_.size()-1),
        waypoints(waypoints_)
        {
            if (waypoints.size() < 2)
            {
                THROW("Track::Track(const std::vector<LongitudeLatitude>&, const Date&, const Date&)", TrackException, "Track should contain at least two waypoints");
            }
            if (arrival_time<departure_time)
            {
                THROW("Track::Track(const std::vector<LongitudeLatitude>&, const Date&, const Date&)", TrackException, "Arrival time should be later than departure time");
            }
            if (departure_time<0)
            {
                THROW("Track::Track(const std::vector<LongitudeLatitude>&, const Date&, const Date&)", TrackException, "Departure time is negative");
            }
            if (arrival_time<0)
            {
                THROW("Track::Track(const std::vector<LongitudeLatitude>&, const Date&, const Date&)", TrackException, "Arrival time is negative");
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

        Date departure_time;
        Date arrival_time;
        std::vector<double> distance_from_start_to_begining_of_leg;
        std::vector<Leg> legs;
        double length;
        size_t nb_of_legs;
        std::vector<LongitudeLatitude> waypoints;

    private:
        TrackImpl();
};

Track::Track(const std::vector<LongitudeLatitude>& waypoints,//!< List of points composing the track (at least two), longitude & latitude given in decimal degrees on the WGS84
             const Date& departure_time,                     //!< Time at the first point (POSIX time)
             const Date& arrival_time                        //!< Time at last point (greater than departure time) (POSIX time)
             ) : pimpl(new Track::TrackImpl(waypoints, departure_time, arrival_time))
{

}

/** \author cec
*  \date 10 avr. 2013, 16:14:48
*  \brief Change arrival time (eg. if it is not know at construction)
*/
void Track::set_arrival_time(const Date& time)
{
    pimpl->arrival_time = time;
}

/** \author cec
 *  \date 11 avr. 2013, 12:55:00
 *  \brief Simple accessor
 *  \returns Time of departure (POSIX time)
*/
Date Track::get_departure_time() const
{
    return pimpl->departure_time;
}

/** \author cec
 *  \date 11 avr. 2013, 14:42:30
 *  \brief Computes the average speed on track
 *  \returns average speed on track (in m/s)
 *  \snippet /unit_tests/src/TrackTest.cpp TrackTest get_average_speed_example
*/
double Track::get_average_speed() const
{
    return pimpl->length / (pimpl->arrival_time - pimpl->departure_time);
}

/** \author cec
 *  \date 11 avr. 2013, 15:26:32
 *  \brief Retrieve the waypoints used to construct the track
 *  \returns List of waypoints
 *  \snippet /unit_tests/src/TrackTest.cpp TrackTest get_waypoints_example
*/
std::vector<LongitudeLatitude> Track::get_waypoints() const
{
    return pimpl->waypoints;
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
LongitudeLatitude Track::find_waypoint_on_track(const double& distance //!< Distance from first waypoint (in meters)
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
