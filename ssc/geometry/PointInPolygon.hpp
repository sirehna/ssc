/*
 * PointInECAZone.hpp
 *
 * \date 21 mars 2013, 18:00:41
 *  \author cec
 */

#ifndef POINTINECAZONE_HPP_
#define POINTINECAZONE_HPP_

#include <vector>
#include "ssc/macros/tr1_macros.hpp"
#include TR1INC(memory)
#include "ssc/geometry/LatitudeLongitude.hpp"
#include "ssc/exception_handling/Exception.hpp"

namespace ssc
{
    namespace geometry
    {
        class PointInPolygonException : public ::ssc::exception_handling::Exception
        {
            public:
                PointInPolygonException(const std::string& message, const std::string& file, const std::string& function, const unsigned int line) :
                    Exception(message, file, function, line)
                {
                }
        };


        /** \author cec
         *  \ingroup geometry
         *  \brief Interface for classes testing whether a point is in a polygon.
         *  \details Implementation for specific coordinate systems (Cartesian, spherical, geographical)
         *  are defined in derived classes. It is a simple wrapper around boost.geometry.
         *  \section ex1 Example
         *  See derived classes.
         */
        class PointInPolygon
        {
            public:
                bool is_in_polygon(const LatitudeLongitude& point) const;
                virtual ~PointInPolygon();
                class PointInPolygonPimpl;

            private:
                PointInPolygon();

            protected:
                PointInPolygon(const std::vector<LatitudeLongitude>& polygon);
                TR1(shared_ptr)<PointInPolygonPimpl> pimpl;
        };
    }
}

#endif /* POINTINECAZONE_HPP_ */
