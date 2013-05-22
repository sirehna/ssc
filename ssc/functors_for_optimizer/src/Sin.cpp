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
#include "Constant.hpp"
#include "FunctorAlgebra.hpp"
#include <cmath>
#include <string>


Sin::Sin(const NodePtr& n_) : Unary(n_)
{
    update_lambda();
}

void Sin::update_lambda()
{
    set_value([n,factor]()->double {return factor*sin(n->get_lambda()());});
}

std::string Sin::get_operator_name() const
{
    return "sin";
}

NodePtr Sin::diff(const StatePtr& state) const
{
    auto du_dstate = n->diff(state);
    auto dv_dstate = Cos(n->clone()).clone();
    if (n->diff(state)->equals_derived(Constant(1)))
    {
        return dv_dstate;
    }
    return du_dstate*dv_dstate;
}


NodePtr Sin::clone() const
{
    return NodePtr(new Sin(*this));
}

bool Sin::is_null() const
{
    return false;
}

bool Sin::equals(const Node& rhs) const
{
    (void) rhs;
        return false;
        //return rhs.equals_derived(*this);
}

std::string Sin::get_type() const
{
    return "Sin";
}
