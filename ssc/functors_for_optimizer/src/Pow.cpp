#include "Pow.hpp"
#include "Sum.hpp"
#include "Multiply.hpp"
#include "Constant.hpp"
#include "NodeVisitor.hpp"
#include "Ln.hpp"
#include "Divide.hpp"
#include "State.hpp"
#include <cmath>
#include "FunctorAlgebra.hpp"

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
    return [n1_,n2_,factor]()->double{
        return factor*(pow(n1_->get_lambda()(),n2_->get_lambda()()));};
}
#include "test_macros.hpp"
#include "Serialize.hpp"
NodePtr Pow::diff(const StatePtr& state) const
{
    NodePtr ret;
    if (n2_->diff(state)->is_null())
    {
        ret = n2_*Pow(n1_,(n2_-1))*(n1_->diff(state));
    }
    else
    {
        ret = Pow(n1_,n2_)*((n2_->diff(state))*Ln(n1_)+n2_*(n1_->diff(state))/n1_);
    }
    ret->multiply_by(factor);
    ret->update_lambda();
    return ret;
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
