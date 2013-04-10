/*
 * Track.cpp
 *
 * \date 8 avr. 2013, 15:16:34
 *  \author cec
 */

#include "Track.hpp"
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/GeodesicLine.hpp>
#include <math.h>
#include <limits>
#include "test_macros.hpp"
#include <sstream>

Track::Track(const std::vector<LongitudeLatitude>& waypoints_,//!< List of points composing the track (at least two), longitude & latitude given in decimal degrees on the WGS84
             const Date& departure_time_,                     //!< Time at the first point (in UTC at GMT)
             const Date& arrival_time_                        //!< Time at last point (greater than departure time) (in UTC at GMT)
             ) :
waypoints(waypoints_),
departure_time(departure_time_),
arrival_time(arrival_time_),
distances_between_waypoints(std::vector<double>()),
distance_from_start_(std::vector<double>()),
azimuth_at_start(std::vector<double>())

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
    distance_from_start_.push_back(0);
    for (size_t i = 0 ; i < (n-1) ; ++i)
    {
        const double d = distance(waypoints.at(i),waypoints.at(i+1));
        distances_between_waypoints.push_back(d);
        azimuth_at_start.push_back(azimuth_at_point_1(waypoints.at(i),waypoints.at(i+1)));
        distance_from_start_.push_back(distance_from_start_.back()+d);
    }
}

/** \author cec
 *  \date 8 avr. 2013, 15:32:27
 *  \brief Computes the sum of the lengths of each segment taken on the WGS84 (geodesic arcs)
 *  \returns Length of the track (in meters)
 */
double Track::length() const
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
    double s12 = 0;
    geod.Inverse(point1.lat, point1.lon, point2.lat, point2.lon, s12);
    return s12;
}

/** \author cec
 *  \date 8 avr. 2013, 18:36:48
 *  \brief Returns the azimuth at point 1 between two points on a geodesic
 *  \returns Azimuth at departure point
 */
double Track::azimuth_at_point_1(const LongitudeLatitude& point1, //!< Coordinates of first point
                                 const LongitudeLatitude& point2  //!< Coordinates of first point
                                ) const
{
    const GeographicLib::Geodesic& geod = GeographicLib::Geodesic::WGS84;
    double az1 = 0;
    double az2 = 0;
    geod.Inverse(point1.lat, point1.lon, point2.lat, point2.lon, az1, az2);
    return az1;
}

/** \author cec
 *  \date 8 avr. 2013, 18:06:31
 *  \brief Find a waypoint on the track, at a given distance from the first point
 *  \returns Point at given distance from start of track
 */
LongitudeLatitude Track::find_waypoint_on_track(const double& distance //!< Distance from first waypoint (in meters)
                                               ) const
{
    if (distance>distance_from_start_.back())
    {
        THROW("Track::find_waypoint_on_track(const double&)", TrackException, "Point is farther than the last point on track");
    }
    if (distance<0)
    {
        THROW("Track::find_waypoint_on_track(const double&)", TrackException, "received a negative distance");
    }
    const size_t idx = find_leg_index(distance);
    COUT(idx);
    const GeographicLib::Geodesic& geod = GeographicLib::Geodesic::WGS84;
    LongitudeLatitude ret(0,0);
    double azi = azimuth_at_start.at(idx);
    COUT(azi);
    COUT(distance_from_start_.at(idx));
    COUT(distance);
    COUT(distance-distance_from_start_.at(idx));
    geod.Direct(waypoints.at(0).lat, waypoints.at(0).lon, azi, distance-distance_from_start_.at(idx), ret.lat, ret.lon);
    return ret;
}

/** \author cec
 *  \date 8 avr. 2013, 18:08:44
 *  \brief When calling find_waypoint_on_track, we need to know the waypoints surrounding the target:
 *  \returns Index of point just before the point at 'distance' from first waypoint (start of track)
 */
size_t Track::find_leg_index(const double& distance_from_start_of_track //!< Distance from first waypoint (in meters)
                             ) const
{
    const size_t n=distance_from_start_.size();
    if (distance_from_start_of_track<=0)
    {
        THROW("Track::find_leg_index(const double&)", TrackException, "Distance from start of track can't be negative");
    }
    for (size_t i = 1 ; i < n ; ++i)
    {
        if (distance_from_start_of_track<=distance_from_start_.at(i)) return i-1;
    }
    return n-1;
}


/** \author cec
 *  \date 9 avr. 2013, 12:58:22
 *  \brief Distance (on track) of waypoint 'waypoint_idx' from the first waypoint
 *  \returns Distance from first waypoint (in meters)
 */
double Track::distance_from_start(const size_t& waypoint_idx) const
{
    return distance_from_start_.at(waypoint_idx);
}
