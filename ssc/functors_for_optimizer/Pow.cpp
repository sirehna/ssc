#include "ssc/functors_for_optimizer/Pow.hpp"
#include "ssc/functors_for_optimizer/Sum.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/functors_for_optimizer/Constant.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"
#include "ssc/functors_for_optimizer/Ln.hpp"
#include "ssc/functors_for_optimizer/Divide.hpp"
#include "ssc/functors_for_optimizer/State.hpp"
#include <cmath>
#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"
#include "ssc/functors_for_optimizer/Null.hpp"

Pow::Pow(const NodePtr& n1, const NodePtr& n2) : Binary(n1,n2)
{
    set_value(get_pow_fun());
}

Pow::Pow(const NodePtr& n1, const double& n2) : Binary(n1,NodePtr(new Constant(n2)))
{
    set_value(get_pow_fun());
}


std::function<double()> Pow::get_pow_fun() const
{
    const auto n1__ = n1_;
    const auto n2__ = n2_;
    const auto factor_ = factor;
    return [n1__,n2__,factor_]()->double{
        return factor_*(pow(n1__->get_lambda()(),n2__->get_lambda()()));};
}

NodePtr Pow::diff(const StatePtr& state) const
{
    NodePtr dthis_dstate;
    if (n2_->is_constant())
    {
        const double val = n2_->get_lambda()();
        if (val == 0)
        {
            dthis_dstate = NodePtr(new Null());
        }
        else if (val == 1)
        {
            dthis_dstate = n1_->diff(state);
        }
        else if (val == 2)
        {
            dthis_dstate = 2*n1_*(n1_->diff(state));
        }
        else
        {
            dthis_dstate = val*Pow(n1_,(val-1))*(n1_->diff(state));
        }
    }
    else
    {
        dthis_dstate = Pow(n1_,n2_)*((n2_->diff(state))*Ln(n1_)+n2_*(n1_->diff(state))/n1_);
    }
    dthis_dstate->multiply_by(factor);
    return dthis_dstate;
}

std::string Pow::get_operator_name() const
{
    return "^";
}

NodePtr Pow::clone() const
{
    return NodePtr(new Pow(*this));
}

bool Pow::is_null() const
{
    return n1_->is_null();
}

bool Pow::equals(const Node& rhs) const
{
    return rhs.equals_derived(*this);
}

bool Pow::equals_derived(const Pow& rhs) const
{
    return ((*n1_==*rhs.n1_)&&(*n2_==*rhs.n2_));
}

std::string Pow::get_type() const
{
    return "Pow";
}

NodePtr Pow::simplify() const
{
    if ((n1_->get_type() == "Constant") && (n2_->get_type() == "Constant"))
    {
        return NodePtr(new Constant(get_lambda()()));
    }
    if (n2_->is_null())           return NodePtr(new Constant(1));
    if (n2_->equals(Constant(1))) return n1_->clone();
                                  return NodePtr(new Pow(*this));
}

void Pow::update_lambda()
{
    set_value(get_pow_fun());
}

bool Pow::is_constant() const
{
    return (n2_->is_null() || (n1_->is_constant() && n2_->is_constant()) || n1_->equals_one());
}

