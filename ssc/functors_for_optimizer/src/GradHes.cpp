/*
 * GradHes.cpp
 *
 * \date 20 févr. 2013, 12:21:18
 *  \author cec
 */

#include "GradHes.hpp"
#include "StateGetter.hpp"

StateList get_states(const NodePtr& objective_function, const std::vector<NodePtr>& constraints)
{
    StateGetter getstates;
    getstates(objective_function);
    getstates(constraints);
    return getstates.get();
}
