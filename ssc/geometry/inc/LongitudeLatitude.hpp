/*
 * LatitudeLongitude.hpp
 *
 * \date 22 mars 2013, 17:42:12
 *  \author cec
 */

#ifndef LATITUDELONGITUDE_HPP_
#define LATITUDELONGITUDE_HPP_

#include "Exception.hpp"

class LatitudeLongitudeException : public Exception
{
    public:
        LatitudeLongitudeException(const char* s) :
                Exception(s)
        {
        }
};


/** \author cec
 *  \brief Stores latitude and longitude information
 *  \details It has the following responsibilities:
 *  - Store geographical coordinates in degrees
 *  - Check that the coordinates are within the (-180°,180°) range at construction
 *  \section ex1 Example
 *  \snippet geometry/unit_tests/src/LongitudeLatitudeTest.cpp LongitudeLatitudeTest example
 *  \section ex2 Expected output
 *  \snippet geometry/unit_tests/src/LongitudeLatitudeTest.cpp LongitudeLatitudeTest expected output
 */

class LongitudeLatitude
{
    public:
        LongitudeLatitude(const double& latitude_in_degrees, const double& longitude_in_degrees);
        double lat;
        double lon;
};

#endif /* LATITUDELONGITUDE_HPP_ */
