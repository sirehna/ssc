/*
 * PiecewiseLinearFunctor.cpp
 *
 * \date 19 f�vr. 2013, 08:35:13
 *  \author cec
 */

#include "ssc/functors_for_optimizer/PiecewiseLinearFunctor.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"
#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/functors_for_optimizer/PiecewiseConstantFunctor.hpp"

PiecewiseLinearFunctor::PiecewiseLinearFunctor(const StatePtr& state_, const double& xmin, const double& xmax, const std::vector<double>& y_values) :
Unary(state_),
f(new ssc::interpolation::LinearInterpolation(xmin,xmax,y_values)),
xmin_(xmin),
xmax_(xmax),
dy(std::vector<double>()),
state(state_)
{
    update_lambda();
    const size_t n = y_values.size();
    const double delta = (xmax-xmin)/((double)(n-1));
    for (size_t i = 0 ; i < n-1 ; ++i)
    {
        dy.push_back(f->df(xmin+((double)i)*delta));
    }
}

void PiecewiseLinearFunctor::update_lambda()
{
    const auto f_ = f;
    const auto state_ = state;
    auto func = [f_,state_]()->double
        {
            return f_->f(state_->get_lambda()());
        };
    set_value(func);
}

NodePtr PiecewiseLinearFunctor::diff(const StatePtr& state) const
{
    if (dy.size() > 1) return NodePtr(new PiecewiseConstantFunctor(state, xmin_, xmax_, dy));
    std::vector<double> y(2,0);
    y[0] = dy.front();
    y[1] = dy.back();
    return NodePtr(new PiecewiseConstantFunctor(state, xmin_, xmax_, y));
}

void PiecewiseLinearFunctor::accept(NodeVisitor& v) const
{
    v.visit(*this);
}

NodePtr PiecewiseLinearFunctor::clone() const
{
    return NodePtr(new PiecewiseLinearFunctor(*this));
}

bool PiecewiseLinearFunctor::is_null() const
{
    return false;
}


bool PiecewiseLinearFunctor::equals_derived(const PiecewiseLinearFunctor& rhs) const
{
    (void) rhs;
    return false;
}

std::string PiecewiseLinearFunctor::get_type() const
{
    return "PiecewiseLinear";
}

std::string PiecewiseLinearFunctor::get_operator_name() const
{
    return "piecewise_linear";
}
