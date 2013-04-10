/*
 * Track.cpp
 *
 * \date 8 avr. 2013, 15:16:34
 *  \author cec
 */

#include "Track.hpp"
#include <GeographicLib/Geodesic.hpp>

Track::Track(const std::vector<LongitudeLatitude>& waypoints_,//!< List of points composing the track (at least two), longitude & latitude given in decimal degrees on the WGS84
             const Date& departure_time_,                     //!< Time at the first point (in UTC at GMT)
             const Date& arrival_time_                        //!< Time at last point (greater than departure time) (in UTC at GMT)
             ) :
waypoints(waypoints_),
departure_time(departure_time_),
arrival_time(arrival_time_),
distances_between_waypoints(std::vector<double>())

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
    const size_t n = waypoints.size();
    for (size_t i = 0 ; i < (n-1) ; ++i)
    {
        distances_between_waypoints.push_back(distance(waypoints.at(i),waypoints.at(i+1)));
    }
}

/** \author cec
 *  \date 8 avr. 2013, 15:32:27
 *  \brief Computes the sum of the lengths of each segment taken on the WGS84 (geodesic arcs)
 *  \returns Length of the track (in meters)
 */
double Track::distance() const
{
    double d = 0;
    for (auto it = distances_between_waypoints.begin() ; it != distances_between_waypoints.end() ; ++it)
    {
        d += *it;
    }
    return d;
}

/** \author cec
 *  \date 8 avr. 2013, 17:37:12
 *  \brief Calculates the shortest distance between two points on the WGS84
 *  \returns Distance in meters between point1 and point2
 */
double Track::distance(const LongitudeLatitude& point1, //!< Coordinates of first point
                       const LongitudeLatitude& point2  //!< Coordinates of first point
                       ) const
{
    const GeographicLib::Geodesic& geod = GeographicLib::Geodesic::WGS84;
    double s12;
    geod.Inverse(point1.lat, point1.lon, point2.lat, point2.lon, s12);
    return s12;
}
