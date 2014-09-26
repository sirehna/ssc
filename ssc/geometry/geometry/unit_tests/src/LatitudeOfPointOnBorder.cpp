/*
 * GetMaxLongitude.cpp
 *
 * \date 27 mars 2013, 17:05:03
 *  \author cec
 */

#include "LatitudeOfPointOnBorder.hpp"
#include "PointInPolygon.hpp"
#include <cmath>

LatitudeOfPointOnBorder::LatitudeOfPointOnBorder(PointInPolygon* eca_zone, const double& eps) : eca(eca_zone), eps_(eps)
{

}

double LatitudeOfPointOnBorder::get_latitude(const double& longitude) const
{
    if (not(eca->is_in_polygon(LatitudeLongitude(eps_,longitude)))) return 0;
    MinMax ret = bisection(std::make_pair(eps_,40),longitude);
    return (ret.second+ret.first)/2.;
}

MinMax LatitudeOfPointOnBorder::bisection(const MinMax& latitude_bounds, const double& longitude) const
{
    if (fabs(latitude_bounds.second-latitude_bounds.first)<eps_) return latitude_bounds;
    const double median_latitude = (latitude_bounds.second+latitude_bounds.first)/2.;
    if (eca->is_in_polygon(LatitudeLongitude(median_latitude,longitude)))
    {
        return bisection(std::make_pair(median_latitude,latitude_bounds.second),longitude);
    }
    return bisection(std::make_pair(latitude_bounds.first,median_latitude),longitude);
}

