/*
 * LegChain.cpp
 *
 *  Created on: May 16, 2014
 *      Author: cady
 */

#include "LegChain.hpp"
#include "Leg.hpp"

LegChain::LegChain() : legs(std::vector<LegPtr>()), first_waypoint(LatitudeLongitude(0,0))
{
}

void LegChain::push_back(const LatitudeLongitude& waypoint1,const LatitudeLongitude& waypoint2)
{
    if (legs.empty()) first_waypoint = waypoint1;
    legs.push_back(make_new(waypoint1,waypoint2));
}

LegPtr LegChain::back() const
{
    return legs.back();
}

LegPtr LegChain::at(const size_t i) const
{
    return legs.at(i);
}

std::pair<LatitudeLongitude, size_t> LegChain::find_closest_point_to(const LatitudeLongitude& point) const
{
    LatitudeLongitude nearest_point = first_waypoint;
    double smallest_distance = 1e300;
    size_t idx = 0;
    for (auto that_leg = legs.begin() ; that_leg != legs.end() ; ++that_leg)
    {
        LatitudeLongitude p = (*that_leg)->find_closest_point_to(point);
        const double d = distance(p,point);
        if (d<smallest_distance)
        {
            nearest_point = p;
            smallest_distance = d;
            idx = that_leg-legs.begin();
        }
    }
    return std::make_pair(nearest_point,idx);
}

std::vector<LegPtr>::const_iterator LegChain::begin() const
{
    return legs.begin();
}

std::vector<LegPtr>::const_iterator LegChain::end() const
{
    return legs.end();
}
