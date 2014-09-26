/*
 * Difference.cpp
 *
 * \date 1 f�vr. 2013, 09:22:47
 *  \author cec
 */

#include "Difference.hpp"
#include "NodeVisitor.hpp"
#include "FunctorAlgebra.hpp"

Difference::Difference(const NodePtr& n1, const NodePtr& n2) : Binary(n1,n2)
{
    update_lambda();
}

void Difference::update_lambda()
{
    const auto n1__ = n1_;
    const auto n2__ = n2_;
    const auto factor_ = factor;
    set_value([n1__,n2__,factor_]()->double
    {
        return factor_*(n1__->get_lambda()()-n2__->get_lambda()());
    });
}

std::string Difference::get_operator_name() const
{
    return "-";
}

NodePtr Difference::clone() const
{
    return NodePtr(new Difference(*this));
}

NodePtr Difference::diff(const StatePtr& state) const
{
    return NodePtr(new Difference(n1_->diff(state),n2_->diff(state)));
}

bool Difference::is_null() const
{
    return *n1_==*n2_;
}

bool Difference::equals(const Node& rhs) const
{
    return rhs.equals_derived(*this);
}

bool Difference::equals_derived(const Difference& rhs) const
{
    return ((*n1_ == *rhs.n1_) && (*n2_ == *rhs.n2_));
}

std::string Difference::get_type() const
{
    return "Difference";
}

NodePtr Difference::simplify() const
{
    return NodePtr(new Difference(*this));
}

bool Difference::is_constant() const
{
    return is_null() || (n1_->is_constant() && n2_->is_constant());
}

