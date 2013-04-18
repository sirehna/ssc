/*
 * Leg.hpp
 *
 * \date 9 avr. 2013, 14:53:36
 *  \author cec
 */

#ifndef LEG_HPP_
#define LEG_HPP_

#include "LongitudeLatitude.hpp"
#include <tr1/memory>
#include "Exception.hpp"

class LegException : public Exception
{
    public:
        LegException(const char* s) :
                Exception(s)
        {
        }
};

/** \author cec
 *  \ingroup geometry
 *  \brief Two waypoints connected by a geodesic on the WGS84.
 *  \details This class has the following responsibility:
 *  - Find a point on track at a given distance from the beginning of the track
 *  \section ex1 Example
 *  \snippet geometry/unit_tests/src/LegTest.cpp LegTest example
 *  \section ex2 Expected output
 *  \snippet geometry/unit_tests/src/LegTest.cpp LegTest expected output
 */
class Leg
{
    public:
        Leg(const LongitudeLatitude& point1, const LongitudeLatitude& point2);
        double length() const;
        LongitudeLatitude find_waypoint_at(const double& distance_from_point1) const;

    private:
        Leg();
        class LegImpl;
        std::tr1::shared_ptr<LegImpl> pimpl;
};

#endif /* LEG_HPP_ */
