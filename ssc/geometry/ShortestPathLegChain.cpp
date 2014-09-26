/*
 * ShortestPathLegChain.cpp
 *
 *  Created on: May 16, 2014
 *      Author: cady
 */

#include "ssc/geometry/ShortestPathLegChain.hpp"
#include "ssc/geometry/ShortestPathLeg.hpp"
#include "ssc/geometry/Leg.hpp"

using namespace ssc::geometry;

LegPtr ShortestPathLegChain::make_new(const LatitudeLongitude& waypoint1,const LatitudeLongitude& waypoint2) const
{
    return LegPtr(new ShortestPathLeg(ShortestPathLeg::build(waypoint1,waypoint2)));
}

double ShortestPathLegChain::distance(const LatitudeLongitude& waypoint1,const LatitudeLongitude& waypoint2) const
{
    ShortestPathLeg leg(ShortestPathLeg::build(waypoint1,waypoint2));
    return leg.length();
}

LegChain* ShortestPathLegChain::make_new() const
{
    return new ShortestPathLegChain();
}
