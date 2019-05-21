/*
 * PointInGeographicalPolygon.cpp
 *
 * \date 27 mars 2013, 15:57:40
 * \author cec
 */

#include "ssc/geometry/PointInGeographicalPolygon.hpp"
#include "ssc/geometry/PointInPolygonPimpl.hpp"

using namespace ssc::geometry;

typedef boost::geometry::model::ll::point<boost::geometry::degree> Point;

namespace ssc
{
    namespace geometry
    {
        template <> boost::geometry::model::ll::point<boost::geometry::degree> convert_to(const double& longitude, const double& latitude)
        {
            boost::geometry::model::ll::point<boost::geometry::degree> p;
            DegreesMinutesSecond lat(latitude);
            DegreesMinutesSecond lon(longitude);
            p.lat(boost::geometry::dms<boost::geometry::north>(lat.degrees, lat.minutes, lat.seconds));
            p.lon(boost::geometry::dms<boost::geometry::east>(lon.degrees, lon.minutes, lon.seconds));
            return p;
        }
    }
}

PointInGeographicalPolygon::PointInGeographicalPolygon(const std::vector<LatitudeLongitude>& polygon) : PointInPolygon(polygon)
{
    pimpl = TR1(shared_ptr)<Pimpl<Point> >(new Pimpl<Point>(polygon));
}
