/*
 * ConstantAzimuthLeg.cpp
 *
 *  Created on: May 14, 2014
 *      Author: cady
 */

#include "ConstantAzimuthLeg.hpp"
#include "ShortestPathLeg.hpp"
#include "loxodrome_on_ellipsoid.hpp"
#include <cmath>

#define PI (4.*atan(1.))
#define RAD (PI/180.)
#define DEG (180./PI)

ConstantAzimuthLeg::ConstantAzimuthLeg(const LatitudeLongitude& point1, const LatitudeLongitude& point2, const double L, const double az12_) : Leg(point1,point2,L),
az12(az12_), latitude_point_1_in_radians(point_1.lat*RAD), longitude_point_1_in_radians(point_1.lon*RAD)
{
}

ConstantAzimuthLeg ConstantAzimuthLeg::build(const LatitudeLongitude& point1, const LatitudeLongitude& point2)
{
    double L = 0;
    double az12 = 0;
    loxodrome_inverse(point1.lat*RAD, point1.lon*RAD, point2.lat*RAD, point2.lon*RAD, L, az12);
    if ((fabs(az12-PI/2)<1E-10) or (fabs(az12+PI/2)<1E-10) or (fabs(az12+1.5*PI)<1E-10))
    {
        L = distance<ShortestPathLeg>(point1,point2);
    }
    return ConstantAzimuthLeg(point1,point2,L,az12);
}

Angle ConstantAzimuthLeg::azimuth_at(const double ) const
{
    return Angle::radian(az12);
}

LatitudeLongitude ConstantAzimuthLeg::find_closest_point_to(const LatitudeLongitude& point) const
{
    return point;
}

LatitudeLongitude ConstantAzimuthLeg::waypoint(const double distance_from_point1) const
{
    double lat = 0;
    double lon = 0;
    loxodrome_direct(latitude_point_1_in_radians, longitude_point_1_in_radians, lat, lon, distance_from_point1, az12);
    return LatitudeLongitude(lat*DEG, lon*DEG);
}

