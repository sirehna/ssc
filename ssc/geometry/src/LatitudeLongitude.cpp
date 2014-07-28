/*
 * LatitudeLongitude.cpp
 *
 * \date 22 mars 2013, 17:43:01
 *  \author cec
 */


#include "LatitudeLongitude.hpp"
#include <cmath>
#include <sstream>
LatitudeLongitude::LatitudeLongitude(const double latitude, const double longitude) : lat(latitude), lon(longitude)
{
    if (fabs(latitude)>90)
    {
        std::stringstream ss;
        ss << "Latitude |" << latitude << "| > 90 deg";
        THROW(__PRETTY_FUNCTION__, LatitudeLongitudeException, ss.str());
    }
    if (fabs(longitude)>180)
    {
        std::stringstream ss;
        ss << "Longitude |" << longitude << "| > 180 deg";
        THROW(__PRETTY_FUNCTION__, LatitudeLongitudeException, ss.str());
    }
}

std::ostream& operator<<(std::ostream& os, const LatitudeLongitude& bar)
{
    return os << "(" << bar.lat << "," << bar.lon << ")";
}

LatitudeLongitude LatitudeLongitude::antipode() const
{
    return LatitudeLongitude(- lat, (lon >=0) ? lon-180. :lon+180 );
}
