/*
 * CubicSplineFunctor.cpp
 *
 * \date 19 f�vr. 2013, 09:39:25
 *  \author cec
 */

#include "ssc/functors_for_optimizer/SplineFunctor.hpp"
#include "ssc/functors_for_optimizer/PiecewiseParabolicFunctor.hpp"
#include "ssc/interpolation/NaturalSplines.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"
#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/interpolation/ParabolicCoefficients.hpp"

class SplineFunctor::Impl
{
    public:
        Impl(const StatePtr& state_, const double& xmin, const double& xmax, const std::vector<double>& y_values) :
                f(new ssc::interpolation::NaturalSplines(xmin,xmax,y_values)),
                xmin_(xmin),
                xmax_(xmax),
                dy(std::vector<ssc::interpolation::ParabolicCoefficients>()),
                state(state_)
        {

        }
        TR1(shared_ptr)<ssc::interpolation::NaturalSplines> f;
        double xmin_;
        double xmax_;
        std::vector<ssc::interpolation::ParabolicCoefficients> dy;
        TR1(shared_ptr)<State> state;
};

SplineFunctor::SplineFunctor(const StatePtr& state_, const double& xmin, const double& xmax, const std::vector<double>& y_values) :
Unary(state_),
pimpl(new Impl(state_, xmin, xmax, y_values))
{
    update_lambda();
}

void SplineFunctor::update_lambda()
{
    const auto pimpl_ = pimpl;
    auto func = [pimpl_]()->double
        {
            return pimpl_->f->f(pimpl_->state->get_lambda()());
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

