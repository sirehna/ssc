/*
 * Cos.cpp
 *
 * \date 1 f�vr. 2013, 14:40:27
 *  \author cec
 */

#include "ssc/functors_for_optimizer/Cos.hpp"
#include "ssc/functors_for_optimizer/Sin.hpp"
#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/functors_for_optimizer/Constant.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/functors_for_optimizer/Parameter.hpp"
#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"
#include <cmath>
#include <string>

using namespace ssc::functors_for_optimizer;

Cos::Cos(const NodePtr& n_) : Unary(n_)
{
    update_lambda();
}

void Cos::update_lambda()
{
    const auto factor_ = factor;
    const auto n_ = n;
    set_value([factor_,n_]()->double {return factor_*std::cos(n_->get_lambda()());});
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
