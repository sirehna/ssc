/*
 * PointInCartesianPolygon.hpp
 *
 * \date 27 mars 2013, 15:56:51
 *  \author cec
 */

#ifndef POINTINCARTESIANPOLYGON_HPP_
#define POINTINCARTESIANPOLYGON_HPP_

#include "PointInPolygon.hpp"

/** \author cec
 *  \brief Checks if a point is in a polygon defined in Cartesian coordinates.
 *  \details It's a simple wrapper around boost.geometry.
 *  \section ex1 Example
 *  \snippet geometry/unit_tests/src/PointInCartesianPolygonTest.cpp PointInCartesianPolygonTest example
 *  \section ex2 Expected output
 *  \snippet geometry/unit_tests/src/PointInCartesianPolygonTest.cpp PointInCartesianPolygonTest expected output
 */

class PointInCartesianPolygon : public PointInPolygon
{
    public:
        PointInCartesianPolygon(const std::vector<LongitudeLatitude>& polygon);
};

#endif /* POINTINCARTESIANPOLYGON_HPP_ */
