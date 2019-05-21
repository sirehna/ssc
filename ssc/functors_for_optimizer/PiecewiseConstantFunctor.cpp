/*
 * PiecewiseConstantFunctor.cpp
 *
 * \date 18 févr. 2013, 17:29:41
 * \author cec
 */

#include "ssc/functors_for_optimizer/PiecewiseConstantFunctor.hpp"
#include "ssc/interpolation/PiecewiseConstant.hpp"
#include "ssc/functors_for_optimizer/Null.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"
#include "ssc/functors_for_optimizer/State.hpp"

using namespace ssc::functors_for_optimizer;

PiecewiseConstantFunctor::PiecewiseConstantFunctor(const StatePtr& state_, const double& xmin, const double& xmax, const std::vector<double>& y_values) :
Unary(state_),
f(new ssc::interpolation::PiecewiseConstant(xmin,xmax,y_values)),
state(state_)
{
    update_lambda();
}

void PiecewiseConstantFunctor::update_lambda()
{
    const auto f_ = f;
    const auto state_ = state;
    auto func = [f_,state_]()->double
        {
            return f_->f(state_->get_lambda()());
        };
    set_value(func);
}

NodePtr PiecewiseConstantFunctor::diff(const StatePtr& state) const
{
    (void) state;
    return NodePtr(new Null);
}

void PiecewiseConstantFunctor::accept(NodeVisitor& v) const
{
    v.visit(*this);
}

NodePtr PiecewiseConstantFunctor::clone() const
{
    return NodePtr(new PiecewiseConstantFunctor(*this));
}

bool PiecewiseConstantFunctor::is_null() const
{
    return false;
}


bool PiecewiseConstantFunctor::equals_derived(const PiecewiseConstantFunctor& rhs) const
{
    (void) rhs;
    return false;
}

std::string PiecewiseConstantFunctor::get_type() const
{
    return "PiecewiseConstant";
}

std::string PiecewiseConstantFunctor::get_operator_name() const
{
    return "piecewise_constant";
}
