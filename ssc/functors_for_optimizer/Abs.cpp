/*
 * Abs.cpp
 *
 * \date 1 févr. 2013, 14:40:27
 * \author cec
 */

#include "ssc/functors_for_optimizer/Abs.hpp"
#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/functors_for_optimizer/Constant.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/functors_for_optimizer/Parameter.hpp"
#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"
#include "ssc/functors_for_optimizer/Sign.hpp"
#include <cmath>
#include <string>

using namespace ssc::functors_for_optimizer;

Abs::Abs(const NodePtr& n_) : Unary(n_)
{
    update_lambda();
}

void Abs::update_lambda()
{
    const auto factor_ = factor;
    const auto n_ = n;
    set_value([factor_,n_]()->double {return factor_*std::abs(n_->get_lambda()());});
}

std::string Abs::get_operator_name() const
{
    return "abs";
}

NodePtr Abs::diff(const StatePtr& state) const
{
    auto du_dstate = n->diff(state);
    auto dv_dstate = Sign(n->clone()).clone();
    return du_dstate*dv_dstate;
}

NodePtr Abs::clone() const
{
    return AbsPtr(new Abs(*this));
}

bool Abs::is_null() const
{
    return get_son()->is_null();
}

std::string Abs::get_type() const
{
    return "Abs";
}

void Abs::accept(NodeVisitor& v) const
{
    v.visit(*this);
}
