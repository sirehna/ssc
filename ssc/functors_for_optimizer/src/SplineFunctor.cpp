/*
 * CubicSplineFunctor.cpp
 *
 * \date 19 févr. 2013, 09:39:25
 *  \author cec
 */

#include "SplineFunctor.hpp"
#include "PiecewiseParabolicFunctor.hpp"
#include "NaturalSplines.hpp"
#include "NodeVisitor.hpp"
#include "State.hpp"

SplineFunctor::SplineFunctor(const StatePtr& state, const double& xmin, const double& xmax, const std::vector<double>& y_values) :
Unary(state),
f(new NaturalSplines(xmin,xmax,y_values)),
xmin_(xmin),
xmax_(xmax),
dy(std::vector<ParabolicCoefficients>())
{
    auto func = [f,state]()->double
        {
            f->set_computed_value(**state);
            return f->f();
        };
    set_value(func);
    dy = f->get_parabolic_coefficients();
}

NodePtr SplineFunctor::diff(const StatePtr& state) const
{
    return NodePtr(new PiecewiseParabolicFunctor(state, xmin_, xmax_, dy));
}

void SplineFunctor::accept(NodeVisitor& v) const
{
    v.visit(*this);
}

NodePtr SplineFunctor::clone() const
{
    return NodePtr(new SplineFunctor(*this));
}

bool SplineFunctor::is_null() const
{
    return false;
}


bool SplineFunctor::equals_derived(const SplineFunctor& rhs) const
{
    (void) rhs;
    return false;
}

std::string SplineFunctor::get_type() const
{
    return "Spline";
}

std::string SplineFunctor::get_operator_name() const
{
    return "spline";
}

