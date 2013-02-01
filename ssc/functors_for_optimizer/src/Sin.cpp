/*
 * Sin.cpp
 *
 * \date 1 févr. 2013, 14:24:01
 *  \author cec
 */

#include "Sin.hpp"
#include "Cos.hpp"
#include "State.hpp"
#include "Node.hpp"
#include "Multiply.hpp"
#include <cmath>
#include <string>

Sin::Sin(const NodePtr& n_) : Unary(n_)
{
    set_value([n]()->double {return sin(n->get_value()());});
}

std::string Sin::get_operator_name() const
{
    return "sin";
}

NodePtr Sin::diff(const StatePtr& state) const
{
    return NodePtr(new Multiply(n->diff(state),CosPtr(new Cos(n))));
}

NodePtr Sin::clone() const
{
    return NodePtr(new Sin(*this));
}
