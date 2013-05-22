/*
 * Divide.cpp
 *
 * \date 1 févr. 2013, 08:59:33
 *  \author cec
 */

#include "Divide.hpp"
#include "State.hpp"
#include "Multiply.hpp"
#include "Difference.hpp"
#include "NodeVisitor.hpp"
#include "Serialize.hpp"
#include "FunctorAlgebra.hpp"

Divide::Divide(const NodePtr& n1, const NodePtr& n2) : Binary(n1,n2)
{
    update_lambda();
}

void Divide::update_lambda()
{
    set_value([n1_,n2_,&factor]()->double{return factor*(n1_->get_lambda()()/n2_->get_lambda()());});
}

NodePtr Divide::diff(const StatePtr& state) const
{
    auto n2_dn1dstate = ((n1_->diff(state))*n2_);
    auto n1_dn2dstate = ((n2_->diff(state))*n1_);
    auto n2_n2 = (n2_*n2_);

    if (n2_dn1dstate->is_null())
    {
        n1_dn2dstate->multiply_by(-1);
        return NodePtr(new Divide(n1_dn2dstate,n2_n2));
    }
    if (n1_dn2dstate->is_null())
    {
        return NodePtr(new Divide(n2_dn1dstate,n2_n2));
    }


    DiffPtr s(new Difference(n2_dn1dstate,n1_dn2dstate));
    return NodePtr(new Divide(s,n2_n2));
}

std::string Divide::get_operator_name() const
{
    return "/";
}

NodePtr Divide::clone() const
{
    return NodePtr(new Divide(*this));
}

bool Divide::is_null() const
{
    return n1_->is_null();
}

bool Divide::equals(const Node& rhs) const
{
    return rhs.equals_derived(*this);
}

bool Divide::equals_derived(const Divide& rhs) const
{
    return (*(n1_*rhs.n2_) == *(n2_*rhs.n1_));
}

std::string Divide::get_type() const
{
    return "Divide";
}

NodePtr Divide::simplify() const
{
    return NodePtr(new Divide(*this));
}

bool Divide::must_parenthesize() const
{
    return true;
}

bool Divide::is_constant() const
{
    return (n1_->is_constant() && n2_->is_constant());
}

