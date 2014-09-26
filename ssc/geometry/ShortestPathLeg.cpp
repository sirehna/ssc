/*
 * Leg.cpp
 *
 * \date 9 avr. 2013, 14:53:36
 *  \author cec
 */

#include "ssc/geometry/ShortestPathLeg.hpp"
#include "ssc/geometry/GreatCircle.h"

#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/GeodesicLine.hpp>
#include <sstream>
#include <cmath>
#include <algorithm> // std::min, std::max

#define PI 4.*atan(1.)
#define EPS 1e-6

using namespace ssc::geometry;

class ShortestPathLeg::LegImpl
{
    public:
        LegImpl(const LatitudeLongitude& point1, const LatitudeLongitude& point2) : geod(GeographicLib::Geodesic::WGS84),direction_of_the_geodesic_at_point_1(0),direction_of_the_geodesic_at_point_2(0),
        geodesic(Geometry::GreatCircle(point1,point2))
        {
            geod.Inverse(point1.lat, point1.lon, point2.lat, point2.lon, direction_of_the_geodesic_at_point_1, direction_of_the_geodesic_at_point_2);
        }

        const GeographicLib::Geodesic& geod;
        double direction_of_the_geodesic_at_point_1;
        double direction_of_the_geodesic_at_point_2;
        Geometry::GreatCircle geodesic;
};

ShortestPathLeg::ShortestPathLeg(const LatitudeLongitude& point1, const LatitudeLongitude& point2, const double L) : Leg(point1,point2,L), pimpl(new LegImpl(point1,point2))
{
}

ShortestPathLeg ShortestPathLeg::build(const LatitudeLongitude& point1, const LatitudeLongitude& point2)
{
    double L = 0;
    GeographicLib::Geodesic::WGS84.Inverse(point1.lat, point1.lon, point2.lat, point2.lon, L);
    return ShortestPathLeg(point1,point2,L);
}


LatitudeLongitude ShortestPathLeg::waypoint(const double distance_from_point1) const
{
    LatitudeLongitude ret(0,0);
    pimpl->geod.Direct(point_1.lat, point_1.lon, pimpl->direction_of_the_geodesic_at_point_1, distance_from_point1, ret.lat, ret.lon);
    return ret;
}

/** \author cec
 *  \date 27 mai 2013, 12:24:45
 *  \brief Calculates the heading of a point on a geodesic
 *  \returns Heading on geodesic for point at a given distance from first point in leg
 *  \snippet geometry/unit_tests/src/Test.cpp LegTest azimuth_at_example
*/
Angle ShortestPathLeg::azimuth_at(const double distance_from_point1) const
{
    double lat2 = 0;
    double lon2 = 0;
    double azi2 = 0;
    double m12 = 0;
    double M12 = 0;
    double M21 = 0;
    double S12 = 0;
    pimpl->geod.Direct(point_1.lat,point_1.lon,pimpl->direction_of_the_geodesic_at_point_1, distance_from_point1, lat2, lon2, azi2,m12, M12, M21, S12);
    return Angle::degree(azi2);
}

/** \author cec
 *  \date 27 mai 2013, 17:22:02
 *  \brief
 *  \returns
 *  \snippet geometry/unit_tests/src/LegTest.cpp LegTest Leg::find_closest_point_to_example
*/
LatitudeLongitude ShortestPathLeg::find_closest_point_to(const LatitudeLongitude& point) const
{
    return pimpl->geodesic.nearestPointTo(point);

}
