/*
 * Leg.hpp
 *
 *  Created on: May 13, 2014
 *      Author: cady
 */

#ifndef LEG_HPP_
#define LEG_HPP_

#include "ssc/geometry/LatitudeLongitude.hpp"
#include "ssc/geometry/Angle.hpp"
#include "ssc/exception_handling/Exception.hpp"

namespace ssc
{
    namespace geometry
    {
        class LegException : public Exception
        {
            public:
                LegException(const char* s) :
                        Exception(s)
                {
                }
        };


        /** \author cec
         *  \date May 13, 2014, 5:24:05 PM
         *  \brief Interface class to choose between loxodrome & geodesic
         *  \details ShortestPathLeg & ConstantAzimuthLeg will derive from this interface
         *  \ingroup geometry
         *  \section ex1 Example
         *  \snippet geometry/unit_tests/src/LegTest.cpp LegTest example
         *  \section ex2 Expected output
         *  \snippet geometry/unit_tests/src/LegTest.cpp LegTest expected output
         */
        class Leg
        {
            public:
                virtual ~Leg();
                double length() const;
                virtual Angle azimuth_at(const double distance_from_point1) const = 0;
                virtual LatitudeLongitude find_closest_point_to(const LatitudeLongitude& point) const = 0;
                LatitudeLongitude find_waypoint_at(const double distance //!< Distance from first waypoint (in meters)
                                                       ) const;

            protected:
                Leg(const LatitudeLongitude& point1, const LatitudeLongitude& point2, const double length_);
                LatitudeLongitude point_1;
                LatitudeLongitude point_2;
                double length_;

            private:
                virtual LatitudeLongitude waypoint(const double distance_from_point1) const = 0;
        };

        template <typename T> double distance(const LatitudeLongitude& A, const LatitudeLongitude& B)
        {
            return T::build(A,B).length();
        }
    }
}

#endif /* LEG_HPP_ */
