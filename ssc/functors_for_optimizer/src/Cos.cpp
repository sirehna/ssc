/*
 * Cos.cpp
 *
 * \date 1 févr. 2013, 14:40:27
 *  \author cec
 */

#include "Cos.hpp"
#include "Sin.hpp"
#include "State.hpp"
#include "Constant.hpp"
#include "Multiply.hpp"
#include "Parameter.hpp"
#include "FunctorAlgebra.hpp"
#include <cmath>
#include <string>


Cos::Cos(const NodePtr& n_) : Unary(n_)
{
    update_lambda();
}

void Cos::update_lambda()
{
    set_value([factor,n]()->double {return factor*cos(n->get_lambda()());});
}

std::string Cos::get_operator_name() const
{
    return "cos";
}

NodePtr Cos::diff(const StatePtr& state) const
{
    auto du_dstate = n->diff(state);
    auto dv_dstate = Sin(n->clone()).clone();
    dv_dstate->multiply_by(-1);
    if (n->diff(state)->equals_derived(Constant(1)))
    {
        return dv_dstate;
    }
    return du_dstate*dv_dstate;
}

NodePtr Cos::clone() const
{
    return NodePtr(new Cos(*this));
}

bool Cos::is_null() const
{
    return false;
}

std::string Cos::get_type() const
{
    return "Cos";
}
