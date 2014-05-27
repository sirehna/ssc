/*
 * ConstantAzimuthLegChain.cpp
 *
 *  Created on: May 16, 2014
 *      Author: cady
 */

#include "ConstantAzimuthLegChain.hpp"
#include "ConstantAzimuthLeg.hpp"

LegPtr ConstantAzimuthLegChain::make_new(const LatitudeLongitude& waypoint1,const LatitudeLongitude& waypoint2) const
{
    return LegPtr(new ConstantAzimuthLeg(ConstantAzimuthLeg::build(waypoint1,waypoint2)));
}

double ConstantAzimuthLegChain::distance(const LatitudeLongitude& waypoint1,const LatitudeLongitude& waypoint2) const
{
    ConstantAzimuthLeg leg(ConstantAzimuthLeg::build(waypoint1,waypoint2));
    return leg.length();
}

LegChain* ConstantAzimuthLegChain::make_new() const
{
    return new ConstantAzimuthLegChain();
}
