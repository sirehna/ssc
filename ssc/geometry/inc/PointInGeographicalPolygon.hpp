/*
 * PointInGeographicalPolygon.hpp
 *
 * \date 27 mars 2013, 15:57:40
 *  \author cec
 */

#ifndef POINTINGEOGRAPHICALPOLYGON_HPP_
#define POINTINGEOGRAPHICALPOLYGON_HPP_

#include "PointInPolygon.hpp"

namespace ssc
{
    namespace geometry
    {
        /** \author cec
         *  \ingroup geometry
         *  \brief Determine if a point is inside a polygon (taken on the WGS84 ellipsoid)
         *  \details  The points are given in (longitude,latitude) in degrees. The ellipsoid parameters are:
         *  - Transverse radius a = 6378137.0 m
            - Conjugate radius b = 6356752.314245 m
         *  \section ex1 Example
         *  \snippet geometry/unit_tests/src/PointInGeographicalPolygonTest.cpp PointInGeographicalPolygonTest example
         *  \section ex2 Expected output
         *  \snippet geometry/unit_tests/src/PointInGeographicalPolygonTest.cpp PointInGeographicalPolygonTest expected output
         */
        class PointInGeographicalPolygon : public PointInPolygon
        {
            public:
                PointInGeographicalPolygon(const std::vector<LatitudeLongitude>& polygon);
        };
    }
}

#endif /* POINTINGEOGRAPHICALPOLYGON_HPP_ */
