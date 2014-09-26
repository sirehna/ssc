/*
 * Leg.hpp
 *
 * \date 9 avr. 2013, 14:53:36
 *  \author cec
 */

#ifndef SHORTEST_PATH_LEG_HPP_
#define SHORTEST_PATH_LEG_HPP_

#include <tr1/memory>
#include "ssc/geometry/Leg.hpp"

namespace ssc
{
    namespace geometry
    {
        /** \author cec
         *  \ingroup geometry
         *  \brief Two waypoints connected by a geodesic on the WGS84.
         *  \details This class has the following responsibility:
         *  - Find a point on track at a given distance from the beginning of the track
         *  \section ex1 Example
         *  \snippet geometry/unit_tests/src/LegTest.cpp LegTest example
         *  \section ex2 Expected output
         *  \snippet geometry/unit_tests/src/LegTest.cpp LegTest expected output
         */
        class ShortestPathLeg : public Leg
        {
            public:
                ShortestPathLeg(const LatitudeLongitude& point1, const LatitudeLongitude& point2, const double L);
                static ShortestPathLeg build(const LatitudeLongitude& point1, const LatitudeLongitude& point2);
                Angle azimuth_at(const double distance_from_point1) const;
                LatitudeLongitude find_closest_point_to(const LatitudeLongitude& point) const;

            private:
                ShortestPathLeg();
                LatitudeLongitude waypoint(const double distance_from_point1) const;
                class LegImpl;
                std::tr1::shared_ptr<LegImpl> pimpl;
        };
    }
}

#endif /* SHORTEST_PATH_LEG_HPP_ */
