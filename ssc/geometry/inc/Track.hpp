/*
 * Track.hpp
 *
 * \date 8 avr. 2013, 15:16:34
 *  \author cec
 */

#ifndef TRACK_HPP_
#define TRACK_HPP_

#include "LongitudeLatitude.hpp"
typedef double Date;
#include <vector>

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
        Track(const std::vector<LongitudeLatitude>& waypoints_, const Date& departure_time_, const Date& arrival_time_);
        double distance() const;

    private:
        Track();
        double distance(const LongitudeLatitude& point1, const LongitudeLatitude& point2) const;

        std::vector<LongitudeLatitude> waypoints;
        Date departure_time;
        Date arrival_time;
        std::vector<double> distances_between_waypoints;
};

#endif /* TRACK_HPP_ */
