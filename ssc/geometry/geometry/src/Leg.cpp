/*
 * Leg.cpp
 *
 * \date 9 avr. 2013, 14:53:36
 *  \author cec
 */

#include "Leg.hpp"
#include "GreatCircle.h"

#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/GeodesicLine.hpp>
#include <sstream>
#include <cmath>
#include <algorithm> // std::min, std::max

#include "test_macros.hpp"

#define PI 4.*atan(1.)
#define EPS 1e-6

class Leg::LegImpl
{
    public:
        LegImpl(const LatitudeLongitude& point1, const LatitudeLongitude& point2) : point_1(point1),point_2(point2),length(0),geod(GeographicLib::Geodesic::WGS84),direction_of_the_geodesic_at_point_1(0),direction_of_the_geodesic_at_point_2(0),
        geodesic(Geometry::GreatCircle(point1,point2))
        {
            geod.Inverse(point1.lat, point1.lon, point2.lat, point2.lon, length);
            geod.Inverse(point1.lat, point1.lon, point2.lat, point2.lon, direction_of_the_geodesic_at_point_1, direction_of_the_geodesic_at_point_2);
        }

        LatitudeLongitude waypoint(const double distance_from_point1) const
        {
            LatitudeLongitude ret(0,0);
            geod.Direct(point_1.lat, point_1.lon, direction_of_the_geodesic_at_point_1, distance_from_point1, ret.lat, ret.lon);
            return ret;
        }

        Angle azimuth_at(const double distance_from_point1) const
        {
            double lat2 = 0;
            double lon2 = 0;
            double azi2 = 0;
            double m12 = 0;
            double M12 = 0;
            double M21 = 0;
            double S12 = 0;
            geod.Direct(point_1.lat,point_1.lon,direction_of_the_geodesic_at_point_1, distance_from_point1, lat2, lon2, azi2,m12, M12, M21, S12);
            return Angle::degree(azi2);
        }

        LatitudeLongitude point_1;
        LatitudeLongitude point_2;
        double length;
        const GeographicLib::Geodesic& geod;
        double direction_of_the_geodesic_at_point_1;
        double direction_of_the_geodesic_at_point_2;
        Geometry::GreatCircle geodesic;
};

Leg::Leg(const LatitudeLongitude& point1, const LatitudeLongitude& point2) : pimpl(new LegImpl(point1,point2))
{

}

/** \author cec
 *  \date 9 avr. 2013, 17:02:49
 *  \brief Length of the leg
 *  \returns Length in meters between point1 and point2, on a geodesic on the WGS84
 *  \snippet /unit_tests/src/LegTest.cpp LegTest length_example
*/
double Leg::length() const
{
    return pimpl->length;
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
    if (distance>(pimpl->length+EPS))
    {
        std::stringstream ss;
        ss << "Asked to find waypoint at d = "
           << distance
           << " m from start of leg but leg is only "
           << pimpl->length
           << " m long (distance - length = " << distance - pimpl->length << " m)";
        THROW(__PRETTY_FUNCTION__, LegException, ss.str());
    }
    if (distance<(-EPS))
    {
        THROW(__PRETTY_FUNCTION__, LegException, "received a negative distance");
    }
    return pimpl->waypoint(std::max(std::min(pimpl->length,distance),0.));
}

/** \author cec
 *  \date 27 mai 2013, 12:24:45
 *  \brief Calculates the heading of a point on a geodesic
 *  \returns Heading on geodesic for point at a given distance from first point in leg
 *  \snippet geometry/unit_tests/src/Test.cpp LegTest azimuth_at_example
*/
Angle Leg::azimuth_at(const double distance_from_point1) const
{
    return pimpl->azimuth_at(distance_from_point1);
}

/** \author cec
 *  \date 27 mai 2013, 17:22:02
 *  \brief
 *  \returns
 *  \snippet geometry/unit_tests/src/LegTest.cpp LegTest Leg::find_closest_point_to_example
*/
LatitudeLongitude Leg::find_closest_point_to(const LatitudeLongitude& point) const
{
    return pimpl->geodesic.nearestPointTo(point);

}
