/*
 * Divide.cpp
 *
 * \date 1 f�vr. 2013, 08:59:33
 *  \author cec
 */

#include "ssc/functors_for_optimizer/Divide.hpp"
#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/functors_for_optimizer/Difference.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"
#include "ssc/functors_for_optimizer/Serialize.hpp"
#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"

using namespace ssc::functors_for_optimizer;

Divide::Divide(const NodePtr& n1, const NodePtr& n2) : Binary(n1,n2)
{
    update_lambda();
}

void Divide::update_lambda()
{
    const auto n1__ = n1_;
    const auto n2__ = n2_;
    const auto factor_ = factor;
    set_value([n1__,n2__,factor_]()->double{return factor_*(n1__->get_lambda()()/n2__->get_lambda()());});
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


void Divide::accept(NodeVisitor& v) const
{
    v.visit(*this);
}
