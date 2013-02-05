/*
 * Constant.cpp
 *
 * \date 5 févr. 2013, 11:22:54
 *  \author cec
 */

#include "Constant.hpp"
#include "Null.hpp"
#include "State.hpp"
#include "NodeVisitor.hpp"

Constant::Constant(const double& v) : val(v)
{
    set_value([&lambda,&val]()->double {return lambda*val;});
}

NodePtr Constant::diff(const StatePtr& state) const
{
    if (state->get_index()){}
    return NodePtr(new Null());
}

bool Constant::operator==(const Constant& rhs) const
{
    return val==rhs.val;
}

bool Constant::operator!=(const Constant& rhs) const
{
    return not(*this==rhs);
}

void Constant::accept(NodeVisitor& v) const
{
    v.visit(*this);
}

NodePtr Constant::clone() const
{
    return NodePtr(new Constant(*this));
}
