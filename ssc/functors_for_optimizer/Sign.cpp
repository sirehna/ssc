/*
 * Sign.cpp
 *
 * \date 1 févr. 2013, 14:40:27
 * \author cec
 */

#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/functors_for_optimizer/Constant.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/functors_for_optimizer/Parameter.hpp"
#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"
#include "ssc/functors_for_optimizer/Sign.hpp"
#include "ssc/functors_for_optimizer/Null.hpp"
#include <cmath>
#include <string>

using namespace ssc::functors_for_optimizer;

Sign::Sign(const NodePtr& n_) : Unary(n_)
{
    update_lambda();
}

void Sign::update_lambda()
{
    const auto factor_ = factor;
    const auto n_ = n;
    set_value([factor_,n_]()->double {return factor_*(n_->get_lambda()() >= 0 ? 1 : -1);});
}

std::string Sign::get_operator_name() const
{
    return "sign";
}

NodePtr Sign::diff(const StatePtr& ) const
{
    return NullPtr(new Null());
}

NodePtr Sign::clone() const
{
    return NodePtr(new Sign(*this));
}

bool Sign::is_null() const
{
    return false;
}

std::string Sign::get_type() const
{
    return "Sign";
}

void Sign::accept(NodeVisitor& v) const
{
    v.visit(*this);
}
