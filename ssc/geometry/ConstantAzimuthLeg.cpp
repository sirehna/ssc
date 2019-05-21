/*
 * ConstantAzimuthLeg.cpp
 *
 * \date May 14, 2014
 * \author cec
 */

#include "ssc/geometry/ConstantAzimuthLeg.hpp"
#include "ssc/geometry/ShortestPathLeg.hpp"
#include "ssc/geometry/loxodrome_on_ellipsoid.hpp"
#include "ssc/geometry/min_search_golden_section.hpp"

#define PI (4.*atan(1.))
#define RAD (PI/180.)
#define DEG (180./PI)

using namespace ssc::geometry;

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

class ClosestPointFunctor
{
    public:
        ClosestPointFunctor(const double lat, const double lon, const double az, const LatitudeLongitude& M_) : lat_A(lat), lon_A(lon), azAB(az), M(M_){}
        double operator()(const double d) const
        {
            double lat, lon;
            loxodrome_direct(lat_A, lon_A, lat, lon, d, azAB);
            return distance<ShortestPathLeg>(M,LatitudeLongitude(lat*DEG,lon*DEG));
        }

    private:
        double lat_A;
        double lon_A;
        double azAB;
        LatitudeLongitude M;
};

LatitudeLongitude ConstantAzimuthLeg::find_closest_point_to(const LatitudeLongitude& M) const
{
    const ClosestPointFunctor f(latitude_point_1_in_radians,longitude_point_1_in_radians, az12, M);
    const double d = min_search_golden_section(f, 0, length_, 1E-10);
    double lat, lon;
    loxodrome_direct(latitude_point_1_in_radians,longitude_point_1_in_radians, lat, lon, d, az12);
    return LatitudeLongitude(lat*DEG,lon*DEG);
}

LatitudeLongitude ConstantAzimuthLeg::waypoint(const double distance_from_point1) const
{
    double lat = 0;
    double lon = 0;
    loxodrome_direct(latitude_point_1_in_radians, longitude_point_1_in_radians, lat, lon, distance_from_point1, az12);
    return LatitudeLongitude(lat*DEG, lon*DEG);
}

