/*
 * Ln.cpp
 *
 * \date 1 févr. 2013, 12:32:08
 *  \author cec
 */

#include "Ln.hpp"
#include "Divide.hpp"
#include "FunctorAlgebra.hpp"
#include <cmath>

Ln::Ln(const NodePtr& n_) : Unary(n_)
{
    update_lambda();
}

void Ln::update_lambda()
{
    set_value([this]()->double {return get_factor()*log(n->get_lambda()());});
}

std::string Ln::get_operator_name() const
{
    return "log";
}

NodePtr Ln::diff(const StatePtr& state) const
{
    return NodePtr(new Divide(n->diff(state),n));
}

NodePtr Ln::clone() const
{
    return NodePtr(new Ln(*this));
}

bool Ln::is_null() const
{
    return n == 1;
}

std::string Ln::get_type() const
{
    return "Ln";
}
