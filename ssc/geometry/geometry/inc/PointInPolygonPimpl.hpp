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

        virtual bool is_in_polygon(const LatitudeLongitude& point) const = 0;
};

template<typename PointType> class Pimpl : public PointInPolygon::PointInPolygonPimpl
{
    public:
        Pimpl(const std::vector<LatitudeLongitude>& points) : polygon(boost::geometry::model::polygon<PointType>())
        {
            if (points.size() < 3)
            {
                THROW(__PRETTY_FUNCTION__, PointInPolygonException, "Need at least three points in polygon");
            }
            const double eps = 1E-15;
            bool polygon_is_closed = (fabs(points.front().lat-points.back().lat)<eps)&&(fabs(points.front().lon-points.back().lon)<eps);
            if (not(polygon_is_closed))
            {
                THROW(__PRETTY_FUNCTION__, PointInPolygonException, "Polygon should be closed");
            }
            for (auto it = points.begin() ; it != points.end() ; ++it)
            {

                const PointType p = convert_to<PointType>(it->lon, it->lat);
                boost::geometry::append(polygon, p);
            }
        }

        bool is_in_polygon(const LatitudeLongitude& point) const
        {
            const PointType p = convert_to<PointType>(point.lon, point.lat);
            return boost::geometry::within(p, polygon);
        }

    private:
        boost::geometry::model::polygon<PointType> polygon;
};


#endif  /* POINTINPOLYGONPIMPL_HPP_ */
