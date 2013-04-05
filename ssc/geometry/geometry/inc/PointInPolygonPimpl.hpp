/*
 * PointInECAZonePimpl.hpp
 *
 * \date 27 mars 2013, 15:42:08
 *  \author cec
 */

#ifndef POINTINPOLYGONPIMPL_HPP_
#define POINTINPOLYGONPIMPL_HPP_

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/extensions/gis/latlong/latlong.hpp>

class DegreesMinutesSecond
{
    public:
        DegreesMinutesSecond(const double& decimal_degrees) : degrees(floor(decimal_degrees)),
                                                              minutes(floor((decimal_degrees-degrees)*60)),
                                                              seconds(decimal_degrees-degrees-minutes/60.)
        {

        }

        int degrees;
        int minutes;
        double seconds;

    private:
        DegreesMinutesSecond();
};

template <typename PointType> PointType convert_to(const double& longitude, const double& latitude);


class PointInPolygon::PointInPolygonPimpl
{
    public:
        virtual ~PointInPolygonPimpl() {}

        virtual bool is_in_polygon(const LongitudeLatitude& point) const = 0;
};

template<typename PointType> class Pimpl : public PointInPolygon::PointInPolygonPimpl
{
    public:
        Pimpl(const std::vector<LongitudeLatitude>& eca_zone) : polygon(boost::geometry::model::polygon<PointType>())
        {
            if (eca_zone.size() < 3)
            {
                THROW("PointInPolygonPimpl(const std::vector<LatitudeLongitude>&)", PointInPolygonException, "Need at least three points in polygon");
            }
            const double eps = 1E-15;
            bool polygon_is_closed = (fabs(eca_zone.front().lat-eca_zone.back().lat)<eps)&&(fabs(eca_zone.front().lon-eca_zone.back().lon)<eps);
            if (not(polygon_is_closed))
            {
                THROW("PointInPolygonPimpl(const std::vector<LatitudeLongitude>&)", PointInPolygonException, "Polygon should be closed");
            }
            for (auto it = eca_zone.begin() ; it != eca_zone.end() ; ++it)
            {

                const PointType p = convert_to<PointType>(it->lon, it->lat);
                boost::geometry::append(polygon, p);
            }
        }

        bool is_in_polygon(const LongitudeLatitude& point) const
        {
            const PointType p = convert_to<PointType>(point.lon, point.lat);
            return boost::geometry::within(p, polygon);
        }

    private:
        boost::geometry::model::polygon<PointType> polygon;
};


#endif  /* POINTINPOLYGONPIMPL_HPP_ */
