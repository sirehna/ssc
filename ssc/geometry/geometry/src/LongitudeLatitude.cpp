/*
 * LatitudeLongitude.cpp
 *
 * \date 22 mars 2013, 17:43:01
 *  \author cec
 */


#include "LongitudeLatitude.hpp"
#include <cmath>

LongitudeLatitude::LongitudeLatitude(const double& longitude, const double& latitude) : lat(latitude), lon(longitude)
{
    if ((fabs(latitude)>180) || (fabs(longitude)>180))
    {
        THROW("LatitudeLongitude::LatitudeLongitude(const double&, const double&)", LatitudeLongitudeException, "Latitude or longitude out of range");
    }
}
