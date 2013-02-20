/*
 * PiecewiseConstantFunctor.cpp
 *
 * \date 18 févr. 2013, 17:29:41
 *  \author cec
 */

#include "PiecewiseConstantFunctor.hpp"
#include "PiecewiseConstant.hpp"
#include "Null.hpp"
#include "NodeVisitor.hpp"
#include "State.hpp"

PiecewiseConstantFunctor::PiecewiseConstantFunctor(const StatePtr& state, const double& xmin, const double& xmax, const std::vector<double>& y_values) :
Unary(state),
f(new PiecewiseConstant(xmin,xmax,y_values))
{
    auto func = [f,state]()->double
        {
            f->set_computed_value(**state);
            return f->f();
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
