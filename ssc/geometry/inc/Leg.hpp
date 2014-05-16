/*
 * Leg.hpp
 *
 *  Created on: May 13, 2014
 *      Author: cady
 */

#ifndef LEG_HPP_
#define LEG_HPP_

#include "LatitudeLongitude.hpp"
#include "Angle.hpp"
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
 *  \date May 13, 2014, 5:24:05 PM
 *  \brief Interface class to choose between loxodrome & geodesic
 *  \details ShortestPathLeg & ConstantAzimuthLeg will derive from this interface
 *  \ingroup geometry
 *  \section ex1 Example
 *  \snippet geometry/unit_tests/src/LegTest.cpp LegTest example
 *  \section ex2 Expected output
 *  \snippet geometry/unit_tests/src/LegTest.cpp LegTest expected output
 */
class Leg
{
    public:
        Leg();
        virtual ~Leg();
        Leg(const LatitudeLongitude& point1, const LatitudeLongitude& point2);
        virtual double length() const = 0;
        virtual LatitudeLongitude find_waypoint_at(const double distance_from_point1) const = 0;
        virtual Angle azimuth_at(const double distance_from_point1) const = 0;
        virtual LatitudeLongitude find_closest_point_to(const LatitudeLongitude& point) const = 0;

    private:
        virtual LatitudeLongitude waypoint(const double distance_from_point1) const = 0;
};


#endif /* LEG_HPP_ */
