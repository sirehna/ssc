/*
 * ConstantAzimuthLegChain.cpp
 *
 * \date May 16, 2014
 * \author cec
 */

#include "ssc/geometry/ConstantAzimuthLegChain.hpp"
#include "ssc/geometry/ConstantAzimuthLeg.hpp"

using namespace ssc::geometry;

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
