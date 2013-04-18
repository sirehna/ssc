/*
 * PiecewiseLinearFunctor.cpp
 *
 * \date 19 févr. 2013, 08:35:13
 *  \author cec
 */

#include "PiecewiseLinearFunctor.hpp"
#include "LinearInterpolation.hpp"
#include "NodeVisitor.hpp"
#include "State.hpp"
#include "PiecewiseConstantFunctor.hpp"

PiecewiseLinearFunctor::PiecewiseLinearFunctor(const StatePtr& state, const double& xmin, const double& xmax, const std::vector<double>& y_values) :
Unary(state),
f(new LinearInterpolation(xmin,xmax,y_values)),
xmin_(xmin),
xmax_(xmax),
dy(std::vector<double>())
{
    auto func = [f,state]()->double
        {
            f->set_computed_value(**state);
            return f->f();
        };
    set_value(func);
    const size_t n = y_values.size();
    const double delta = (xmax-xmin)/(n-1);
    for (size_t i = 0 ; i < n-1 ; ++i)
    {
        f->set_computed_value(xmin+i*delta);
        dy.push_back(f->df());
    }
}

NodePtr PiecewiseLinearFunctor::diff(const StatePtr& state) const
{
    if (dy.size() > 1) return NodePtr(new PiecewiseConstantFunctor(state, xmin_, xmax_, dy));
    return NodePtr(new PiecewiseConstantFunctor(state, xmin_, xmax_, {dy.front(),dy.front()}));
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
