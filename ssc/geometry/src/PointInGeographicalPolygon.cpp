/*
 * PointInGeographicalPolygon.cpp
 *
 * \date 27 mars 2013, 15:57:40
 *  \author cec
 */

#include "PointInGeographicalPolygon.hpp"
#include "PointInPolygonPimpl.hpp"

typedef boost::geometry::model::ll::point<boost::geometry::degree> Point;
//typedef boost::geometry::model::ll::point<boost::geometry::cs::geographic<boost::geometry::degree> > Point;


template <> boost::geometry::model::ll::point<boost::geometry::degree> convert_to(const double& longitude, const double& latitude)
{
    boost::geometry::model::ll::point<boost::geometry::degree> p;
    DegreesMinutesSecond lat(latitude);
    DegreesMinutesSecond lon(longitude);
    p.lat(boost::geometry::dms<boost::geometry::north>(lat.degrees, lat.minutes, lat.seconds));
    p.lon(boost::geometry::dms<boost::geometry::east>(lon.degrees, lon.minutes, lon.seconds));
    return p;
}

PointInGeographicalPolygon::PointInGeographicalPolygon(const std::vector<LongitudeLatitude>& polygon) : PointInPolygon(polygon)
{
    pimpl = std::tr1::shared_ptr<Pimpl<Point> >(new Pimpl<Point>(polygon));
}
