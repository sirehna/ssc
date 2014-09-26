/*
 * PointInCartesianPolygon.cpp
 *
 * \date 27 mars 2013, 15:56:51
 *  \author cec
 */

#include "ssc/geometry/PointInCartesianPolygon.hpp"
#include "ssc/geometry/PointInPolygonPimpl.hpp"

using namespace ssc::geometry;

typedef boost::geometry::model::d2::point_xy<double> Point;

namespace ssc
{
    namespace geometry
    {
        template <> boost::geometry::model::d2::point_xy<double> convert_to(const double& longitude, const double& latitude)
        {
            return boost::geometry::model::d2::point_xy<double>(longitude,latitude);
        }
    }
}

PointInCartesianPolygon::PointInCartesianPolygon(const std::vector<LatitudeLongitude>& polygon) : PointInPolygon(polygon)
{
    pimpl = std::tr1::shared_ptr<Pimpl<Point> >(new Pimpl<Point>(polygon));
}
