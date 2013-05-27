/*
 * PointInECAZone.cpp
 *
 * \date 21 mars 2013, 18:00:41
 *  \author cec
 */



#include "PointInPolygon.hpp"

#include "PointInPolygonPimpl.hpp"


PointInPolygon::~PointInPolygon()
{

}

typedef boost::geometry::model::d2::point_xy<double> Point;

PointInPolygon::PointInPolygon(const std::vector<LatitudeLongitude>& polygon) : pimpl(new Pimpl<Point>(polygon))
{
    
}

bool PointInPolygon::is_in_polygon(const LatitudeLongitude& point) const
{
    return pimpl->is_in_polygon(point);
}
