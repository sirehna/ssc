/*
 * LatitudeLongitude.hpp
 *
 * \date 22 mars 2013, 17:42:12
 *  \author cec
 */

#ifndef LATITUDELONGITUDE_HPP_
#define LATITUDELONGITUDE_HPP_

#include <iostream>

#include "ssc/exception_handling/Exception.hpp"

namespace ssc
{
    namespace geometry
    {
        class LatitudeLongitudeException : public ::ssc::exception_handling::Exception
        {
            public:
                LatitudeLongitudeException(const std::string& message, const std::string& file, const std::string& function, const unsigned int line) :
                    Exception(message, file, function, line)
                {
                }
        };


        /** \author cec
         *  \ingroup geometry
         *  \brief Stores latitude and longitude information
         *  \details It has the following responsibilities:
         *  - Store geographical coordinates in degrees
         *  - Check that the coordinates are within the (-180 deg,180 deg) range at construction
         *  \section ex1 Example
         *  \snippet geometry/unit_tests/src/LongitudeLatitudeTest.cpp LongitudeLatitudeTest example
         *  \section ex2 Expected output
         *  \snippet geometry/unit_tests/src/LongitudeLatitudeTest.cpp LongitudeLatitudeTest expected output
         */

        class LatitudeLongitude
        {
            public:
                LatitudeLongitude();
                LatitudeLongitude(const double latitude_in_degrees, const double longitude_in_degrees);
                double lat;
                double lon;
                LatitudeLongitude antipode() const;
        };
    }
}

std::ostream& operator<<(std::ostream& os, const ssc::geometry::LatitudeLongitude& bar);


#endif /* LATITUDELONGITUDE_HPP_ */
