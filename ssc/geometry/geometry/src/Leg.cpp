/*
 * Leg.cpp
 *
 * \date 9 avr. 2013, 14:53:36
 *  \author cec
 */

#include "Leg.hpp"
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/GeodesicLine.hpp>
#include <sstream>

#define EPS 1e-6
#define max(a,b) (a) > (b) ? (a) : (b)
#define min(a,b) (a) < (b) ? (a) : (b)

class Leg::LegImpl
{
    public:
        LegImpl(const LongitudeLatitude& point1, const LongitudeLatitude& point2) : point_1(point1),point_2(point2),length(0),geod(GeographicLib::Geodesic::WGS84),direction_of_the_geodesic_at_point_1(0)
        {
            geod.Inverse(point1.lat, point1.lon, point2.lat, point2.lon, length);
            double az2 = 0;
            geod.Inverse(point1.lat, point1.lon, point2.lat, point2.lon, direction_of_the_geodesic_at_point_1, az2);
        }

        LongitudeLatitude waypoint(const double& distance_from_point1) const
        {
            LongitudeLatitude ret(0,0);
            geod.Direct(point_1.lat, point_1.lon, direction_of_the_geodesic_at_point_1, distance_from_point1, ret.lat, ret.lon);
            return ret;
        }
        LongitudeLatitude point_1;
        LongitudeLatitude point_2;
        double length;
        const GeographicLib::Geodesic& geod;
        double direction_of_the_geodesic_at_point_1;
};

Leg::Leg(const LongitudeLatitude& point1, const LongitudeLatitude& point2) : pimpl(new LegImpl(point1,point2))
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
LongitudeLatitude Leg::find_waypoint_at(const double& distance //!< Distance from first waypoint (in meters)
                                       ) const
{
    if (distance>(pimpl->length+EPS))
    {
        std::stringstream ss;
        ss << "Asked to find waypoint at d = "
           << distance
           << " m from start of track but length of track is only "
           << pimpl->length
           << " m long (distance - length = " << distance - pimpl->length << " m)";
        THROW("Leg::find_waypoint_at(const double&)", LegException, ss.str());
    }
    if (distance<(-EPS))
    {
        THROW("Leg::find_waypoint_at(const double&)", LegException, "received a negative distance");
    }
    return pimpl->waypoint(max(min(pimpl->length,distance),0));
}

