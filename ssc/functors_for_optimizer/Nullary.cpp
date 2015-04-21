/*
 * Nullary.cpp
 *
 * \date 29 janv. 2013, 09:38:54
 *  \author cec
 */

#include "ssc/functors_for_optimizer/Nullary.hpp"

using namespace ssc::functors_for_optimizer;

Nullary::Nullary() : Node()
{
    factor = 1;
}

Nullary::Nullary(const double& val)
{
    factor = val;
}

void Nullary::set_value(const std::function<double()>& val)
{
    value = val;
}
