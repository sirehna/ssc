/*
 * Cos.cpp
 *
 * \date 1 févr. 2013, 14:40:27
 *  \author cec
 */

#include "Cos.hpp"
#include "Sin.hpp"
#include "State.hpp"
#include "Multiply.hpp"
#include "Parameter.hpp"
#include "FunctorAlgebra.hpp"
#include <cmath>
#include <string>

Cos::Cos(const NodePtr& n_) : Unary(n_)
{
    set_value([n]()->double {return cos(n->get_value()());});
}

std::string Cos::get_operator_name() const
{
    return "cos";
}

NodePtr Cos::diff(const StatePtr& state) const
{
    return (-1.)*n->diff(state)*Sin(n->clone());

    //return NodePtr(new Multiply(Mult(new Multiply(n->diff(state),ConstantPtr(new Constant(-1)))),SinPtr(new Sin(n))));
}

NodePtr Cos::clone() const
{
    return NodePtr(new Cos(*this));
}
