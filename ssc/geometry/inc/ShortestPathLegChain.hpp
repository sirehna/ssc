/*
 * ShortestPathLegChain.hpp
 *
 *  Created on: May 16, 2014
 *      Author: cady
 */

#ifndef SHORTESTPATHLEGCHAIN_HPP_
#define SHORTESTPATHLEGCHAIN_HPP_

#include "LegChain.hpp"

namespace ssc
{
    namespace geometry
    {
        /** \author cec
         *  \date May 16, 2014, 5:16:56 PM
         *  \brief
         *  \details
         *  \ingroup geometry
         *  \section ex1 Example
         *  \snippet geometry/unit_tests/src/ShortestPathLegChainTest.cpp ShortestPathLegChainTest example
         *  \section ex2 Expected output
         *  \snippet geometry/unit_tests/src/ShortestPathLegChainTest.cpp ShortestPathLegChainTest expected output
         */
        class ShortestPathLegChain : public LegChain
        {
            private:
                LegPtr make_new(const LatitudeLongitude& waypoint1,const LatitudeLongitude& waypoint2) const;
                double distance(const LatitudeLongitude& waypoint1,const LatitudeLongitude& waypoint2) const;
                LegChain* make_new() const;
        };
    }
}

#endif /* SHORTESTPATHLEGCHAIN_HPP_ */
