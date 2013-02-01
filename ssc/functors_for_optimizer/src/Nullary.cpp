/*
 * Nullary.cpp
 *
 * \date 29 janv. 2013, 09:38:54
 *  \author cec
 */

#include "Nullary.hpp"

Nullary::Nullary() : Node()
{
    lambda = 1;
}

Nullary::Nullary(const double& val)
{
    lambda = val;
}

void Nullary::set_value(const std::function<double()>& val)
{
    value = val;
}
