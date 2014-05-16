/*
 * ConstantAzimuthLeg.hpp
 *
 *  Created on: May 14, 2014
 *      Author: cady
 */

#ifndef CONSTANTAZIMUTHLEG_HPP_
#define CONSTANTAZIMUTHLEG_HPP_

#include "Leg.hpp"

/** \author cec
 *  \date May 14, 2014, 11:04:10 AM
 *  \brief Loxodrome curve between two points on the WGS84 ellipsoid.
 *  \ingroup geometry
 *  \section ex1 Example
 *  \snippet geometry/unit_tests/src/ConstantAzimuthLegTest.cpp ConstantAzimuthLegTest example
 *  \section ex2 Expected output
 *  \snippet geometry/unit_tests/src/ConstantAzimuthLegTest.cpp ConstantAzimuthLegTest expected output
 */
class ConstantAzimuthLeg : public Leg
{
    public:
        ConstantAzimuthLeg(const LatitudeLongitude& point1, const LatitudeLongitude& point2, const double L, const double az12);
        static ConstantAzimuthLeg build(const LatitudeLongitude& point1, const LatitudeLongitude& point2);
        Angle azimuth_at(const double distance_from_point1) const;
        LatitudeLongitude find_closest_point_to(const LatitudeLongitude& point) const;

    private:
        ConstantAzimuthLeg();
        LatitudeLongitude waypoint(const double distance_from_point1) const;

        double az12;
        double latitude_point_1_in_radians;
        double longitude_point_1_in_radians;
};

#endif /* CONSTANTAZIMUTHLEG_HPP_ */
