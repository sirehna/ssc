/*
 * Ln.cpp
 *
 * \date 1 févr. 2013, 12:32:08
 *  \author cec
 */

#include "Ln.hpp"
#include "Divide.hpp"
#include <cmath>

Ln::Ln(const NodePtr& n_) : Unary(n_)
{
    set_value([n]()->double {return log(n->get_value()());});
}

std::string Ln::get_operator_name() const
{
    return "log";
}

NodePtr Ln::diff(const StatePtr& state) const
{
    return NodePtr(new Divide(n->diff(state),n));
}
