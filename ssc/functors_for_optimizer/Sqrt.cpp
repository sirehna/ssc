/*
 * Cos.cpp
 *
 * \date 1 f�vr. 2013, 14:40:27
 *  \author cec
 */

#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/functors_for_optimizer/Constant.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/functors_for_optimizer/Parameter.hpp"
#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"
#include "ssc/functors_for_optimizer/Sqrt.hpp"
#include "ssc/functors_for_optimizer/Null.hpp"
#include "ssc/functors_for_optimizer/Divide.hpp"
#include <cmath>
#include <string>

using namespace ssc::functors_for_optimizer;

Sqrt::Sqrt(const NodePtr& n_) : Unary(n_)
{
    update_lambda();
}

void Sqrt::update_lambda()
{
    const auto factor_ = factor;
    const auto n_ = n;
    set_value([factor_,n_]()->double {return factor_*std::sqrt(n_->get_lambda()());});
}

std::string Sqrt::get_operator_name() const
{
    return "sqrt";
}

NodePtr Sqrt::diff(const StatePtr& x) const
{
    NodePtr dn_dx = n->diff(x);
    if (n->is_null()) return NullPtr(new Null());
    if (dn_dx->is_null()) return NullPtr(new Null());
    NodePtr s = clone();
    s->multiply_by(2);
    return Divide(dn_dx,s).clone();
}

NodePtr Sqrt::clone() const
{
    return SqrtPtr(new Sqrt(*this));
}

bool Sqrt::is_null() const
{
    return n->is_null();
}

std::string Sqrt::get_type() const
{
    return "Sqrt";
}

void Sqrt::accept(NodeVisitor& v) const
{
    v.visit(*this);
}
