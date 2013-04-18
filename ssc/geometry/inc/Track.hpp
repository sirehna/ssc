/*
 * Track.hpp
 *
 * \date 8 avr. 2013, 15:16:34
 *  \author cec
 */

#ifndef TRACK_HPP_
#define TRACK_HPP_

#include "LongitudeLatitude.hpp"
#include <vector>
#include <tr1/memory>
#include "Exception.hpp"

class TrackException : public Exception
{
    public:
        TrackException(const char* s) :
                Exception(s)
        {
        }
};


/** \author cec
 *  \brief A track has at least two waypoints, a departure time & an arrival time
 *  \details It has the following responsibilities:
 *  - Should be able to find the distance between two points (spherical & WGS84)
 *  - Can find a point on track at a given distance from the beginning of the track
 *  All these functionalities are basically implemented in GeographicLib: this class is merely a wrapper.
 *  \section ex1 Example
 *  \snippet geometry/unit_tests/src/TrackTest.cpp TrackTest example
 *  \section ex2 Expected output
 *  \snippet geometry/unit_tests/src/TrackTest.cpp TrackTest expected output
 */
class Track
{
    public:
        Track(const std::vector<LongitudeLatitude>& waypoints);
        double length() const;
        LongitudeLatitude find_waypoint_on_track(const double& distance_from_start_of_track) const;
        size_t find_leg_index(const double& distance_from_start_of_track) const;
        double get_waypoint_position_on_track(const size_t& waypoint_idx) const;
        std::vector<LongitudeLatitude> get_all_waypoints() const;
        std::vector<LongitudeLatitude> get_waypoints_closer_than(const double& distance_from_beginning_of_track) const;
        std::vector<LongitudeLatitude> get_waypoints_further_than(const double& distance_from_beginning_of_track) const;

    private:
        Track();
        class TrackImpl;
        std::tr1::shared_ptr<TrackImpl> pimpl;
};

#endif /* TRACK_HPP_ */
