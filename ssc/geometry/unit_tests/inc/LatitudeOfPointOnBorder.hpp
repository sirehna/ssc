/*
 * GetMaxLongitude.hpp
 *
 * \date 27 mars 2013, 17:05:03
 * \author cec
 */

#ifndef GETMAXLONGITUDE_HPP_
#define GETMAXLONGITUDE_HPP_

#include "ssc/macros/tr1_macros.hpp"
#include TR1INC(memory)
#include <map>

/** \author cec
 *  \brief This class was created to find a point on the border of a polygon, given its longitude
 */


namespace ssc
{
    namespace geometry
    {
        class PointInPolygon;
        typedef std::pair<double,double> MinMax;

        class LatitudeOfPointOnBorder
        {
            public:
                LatitudeOfPointOnBorder(PointInPolygon* eca_zone, const double& eps);
                double get_latitude(const double& longitude) const;

            private:
                LatitudeOfPointOnBorder();
                MinMax bisection(const MinMax& latitude_bounds, const double& longitude) const;
                TR1(shared_ptr)<PointInPolygon> eca;
                double eps_;

        };
    }
}

#endif /* GETMAXLONGITUDE_HPP_ */
