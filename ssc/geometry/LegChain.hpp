/*
 * LegChain.hpp
 *
 *  Created on: May 16, 2014
 *      Author: cady
 */

#ifndef LEGCHAIN_HPP_
#define LEGCHAIN_HPP_

#include "ssc/macros/tr1_macros.hpp"
#include TR1INC(memory)
#include <vector>

#include "ssc/geometry/LatitudeLongitude.hpp"

namespace ssc
{
    namespace geometry
    {
        class Leg;
        typedef TR1(shared_ptr)<Leg> LegPtr;

        /** \author cec
         *  \date May 16, 2014, 4:28:13 PM
         *  \brief Abstracts away the Leg creation (so Track doesn't need to know what types of Legs exist)
         *  \ingroup geometry
         *  \section ex1 Example
         *  \snippet geometry/unit_tests/src/LegChainTest.cpp LegChainTest example
         *  \section ex2 Expected output
         *  \snippet geometry/unit_tests/src/LegChainTest.cpp LegChainTest expected output
         */
        class LegChain
        {
            public:
                LegChain();
                virtual ~LegChain(){}
                void push_back(const LatitudeLongitude& waypoint1,const LatitudeLongitude& waypoint2);
                LegPtr back() const;
                LegPtr at(const size_t i) const;
                std::pair<LatitudeLongitude, size_t> find_closest_point_to(const LatitudeLongitude& point) const;
                virtual LegChain* make_new() const = 0;
                std::vector<LegPtr>::const_iterator begin() const;
                std::vector<LegPtr>::const_iterator end() const;

            private:
                virtual LegPtr make_new(const LatitudeLongitude& waypoint1,const LatitudeLongitude& waypoint2) const = 0;
                virtual double distance(const LatitudeLongitude& waypoint1,const LatitudeLongitude& waypoint2) const = 0;
                std::vector<LegPtr> legs;
                LatitudeLongitude first_waypoint;
        };
    }
}

#endif /* LEGCHAIN_HPP_ */
