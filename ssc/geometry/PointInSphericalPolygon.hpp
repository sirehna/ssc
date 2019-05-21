/*
 * PointInSphericalPolygon.hpp
 *
 * \date 27 mars 2013, 15:57:14
 * \author cec
 */

#ifndef POINTINSPHERICALPOLYGON_HPP_
#define POINTINSPHERICALPOLYGON_HPP_

#include "ssc/geometry/PointInPolygon.hpp"

namespace ssc
{
    namespace geometry
    {
        /** \author cec
         *  \ingroup geometry
         *  \brief Check if a point is in a polygon defined on a sphere.
         *  \details The points are given in (longitude,latitude) in degrees.
         *  \section ex1 Example
         *  \snippet geometry/unit_tests/src/PointInSphericalPolygonTest.cpp PointInSphericalPolygonTest example
         *  \section ex2 Expected output
         *  \snippet geometry/unit_tests/src/PointInSphericalPolygonTest.cpp PointInSphericalPolygonTest expected output
         */
        class PointInSphericalPolygon : public PointInPolygon
        {
            public:
                PointInSphericalPolygon(const std::vector<LatitudeLongitude>& polygon);
        };
    }
}

#endif /* POINTINSPHERICALPOLYGON_HPP_ */
