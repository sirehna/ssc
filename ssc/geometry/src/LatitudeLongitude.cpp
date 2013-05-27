/*
 * LatitudeLongitude.cpp
 *
 * \date 22 mars 2013, 17:43:01
 *  \author cec
 */


#include "LatitudeLongitude.hpp"
#include <cmath>

LatitudeLongitude::LatitudeLongitude(const double& latitude, const double& longitude) : lat(latitude), lon(longitude)
{
    if ((fabs(latitude)>90) || (fabs(longitude)>180))
    {
        THROW("LatitudeLongitude::LatitudeLongitude(const double& latitude, const double& longitude)", LatitudeLongitudeException, "Latitude or longitude out of range");
    }
}

std::ostream& operator<<(std::ostream& os, const LatitudeLongitude& bar)
{
    return os << "(" << bar.lat << "," << bar.lon << ")";
}
