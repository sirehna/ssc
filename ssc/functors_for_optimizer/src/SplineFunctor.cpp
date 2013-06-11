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
#include "ParabolicCoefficients.hpp"

class SplineFunctor::Impl
{
    public:
        Impl(const StatePtr& state_, const double& xmin, const double& xmax, const std::vector<double>& y_values) : f(new NaturalSplines(xmin,xmax,y_values)),
                xmin_(xmin),
                xmax_(xmax),
                dy(std::vector<ParabolicCoefficients>()),
                state(state_)
        {

        }
        std::tr1::shared_ptr<NaturalSplines> f;
        double xmin_;
        double xmax_;
        std::vector<ParabolicCoefficients> dy;
        std::tr1::shared_ptr<State> state;
};

SplineFunctor::SplineFunctor(const StatePtr& state_, const double& xmin, const double& xmax, const std::vector<double>& y_values) :
Unary(state_),
pimpl(new Impl(state_, xmin, xmax, y_values))
{
    update_lambda();
}

void SplineFunctor::update_lambda()
{
    auto func = [pimpl]()->double
        {
            pimpl->f->set_computed_value(pimpl->state->get_lambda()());
            return pimpl->f->f();
        };
    set_value(func);
    pimpl->dy = pimpl->f->get_parabolic_coefficients();
}

NodePtr SplineFunctor::diff(const StatePtr& state) const
{
    return NodePtr(new PiecewiseParabolicFunctor(state, pimpl->xmin_, pimpl->xmax_, pimpl->dy));
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

