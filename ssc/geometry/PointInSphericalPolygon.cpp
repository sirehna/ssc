/*
 * PointInSphericalPolygon.cpp
 *
 * \date 27 mars 2013, 15:57:14
 *  \author cec
 */

#include "ssc/geometry/PointInSphericalPolygon.hpp"
#include "ssc/geometry/PointInPolygonPimpl.hpp"

namespace ssc
{
    namespace geometry
    {
        typedef boost::geometry::model::point<double, 2, boost::geometry::cs::spherical_equatorial<boost::geometry::degree> > Point;


        template <> boost::geometry::model::point<double, 2, boost::geometry::cs::spherical_equatorial<boost::geometry::degree> > convert_to(const double& longitude, const double& latitude)
        {
            return boost::geometry::model::point<double, 2, boost::geometry::cs::spherical_equatorial<boost::geometry::degree> >(longitude,latitude);
        }

        PointInSphericalPolygon::PointInSphericalPolygon(const std::vector<LatitudeLongitude>& polygon) : PointInPolygon(polygon)
        {
            pimpl = TR1(shared_ptr)<Pimpl<Point> >(new Pimpl<Point>(polygon));
        }
    }
}
