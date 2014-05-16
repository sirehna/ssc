/*
 * Leg.cpp
 *
 *  Created on: May 13, 2014
 *      Author: cady
 */

#include "Leg.hpp"
#include <sstream>

#define EPS 1e-6

Leg::Leg(const LatitudeLongitude& point1, const LatitudeLongitude& point2) : length_(0), point_1(point1), point_2(point2)
{
}

Leg::~Leg()
{
}

/** \author cec
 *  \date 9 avr. 2013, 15:38:04
 *  \brief Find a waypoint on the leg, at a given distance from the first point
 *  \returns Point at given distance from start of leg
 *  \section ex1 Example
 *  \snippet geometry/unit_tests/src/LegTest.cpp LegTest find_waypoint_at_example
 */
LatitudeLongitude Leg::find_waypoint_at(const double distance //!< Distance from first waypoint (in meters)
                                       ) const
{
    if (distance>(length_+EPS))
    {
        std::stringstream ss;
        ss << "Asked to find waypoint at d = "
           << distance
           << " m from start of leg but leg is only "
           << length_
           << " m long (distance - length = " << distance - length_ << " m)";
        THROW(__PRETTY_FUNCTION__, LegException, ss.str());
    }
    if (distance<(-EPS))
    {
        THROW(__PRETTY_FUNCTION__, LegException, "received a negative distance");
    }
    return waypoint(std::max(std::min(length_,distance),0.));
}

/** \author cec
 *  \date 9 avr. 2013, 17:02:49
 *  \brief Length of the leg
 *  \returns Length in meters between point1 and point2, on a geodesic on the WGS84
 *  \snippet geometry/unit_tests/src/LegTest.cpp LegTest length_example
*/
double Leg::length() const
{
    return length_;
}
