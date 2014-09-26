/*
 * LatitudeLongitude.cpp
 *
 * \date 22 mars 2013, 17:43:01
 *  \author cec
 */


#include "ssc/geometry/LongitudeLatitude.hpp"
#include <cmath>

using namespace ssc::geometry;

LongitudeLatitude::LongitudeLatitude(const double& longitude, const double& latitude) : lat(latitude), lon(longitude)
{
    if ((fabs(latitude)>90) || (fabs(longitude)>180))
    {
        THROW("LatitudeLongitude::LatitudeLongitude(const double&, const double&)", LatitudeLongitudeException, "Latitude or longitude out of range");
    }
}

std::ostream& operator<<(std::ostream& os, const LongitudeLatitude& bar)
{
    return os << "(" << bar.lon << "," << bar.lat << ")";
}
