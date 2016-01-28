/*
 * LegChain.cpp
 *
 *  Created on: May 16, 2014
 *      Author: cady
 */

#include "ssc/geometry/LegChain.hpp"
#include "ssc/geometry/Leg.hpp"

using namespace ssc::geometry;

LegChain::LegChain() : legs(std::vector<LegPtr>()), first_waypoint(LatitudeLongitude(0,0))
{
}

void LegChain::push_back(const LatitudeLongitude& waypoint1,const LatitudeLongitude& waypoint2)
{
    if (legs.empty()) first_waypoint = waypoint1;
    legs.push_back(make_new(waypoint1,waypoint2));
}

size_t LegChain::size() const
{
    return legs.size();
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
    double smallest_distance = distance(nearest_point, point);
    size_t idx = 0;
    for (size_t i = 1 ; i < legs.size() ; ++i)
    {
        LatitudeLongitude p = (legs[i])->find_closest_point_to(point);
        const double d = distance(p,point);
        if (d<smallest_distance)
        {
            nearest_point = p;
            smallest_distance = d;
            idx = i;
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
