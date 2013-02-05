#include "Pow.hpp"
#include "Sum.hpp"
#include "Multiply.hpp"
#include "Constant.hpp"
#include "NodeVisitor.hpp"
#include "Ln.hpp"
#include "Divide.hpp"
#include <cmath>

Pow::Pow(const NodePtr& n1, const NodePtr& n2) : Binary(n1,n2)
{
    set_value(get_pow_fun());
}

Pow::Pow(const NodePtr& n1, const double& n2) : Binary(n1, std::tr1::shared_ptr<Parameter>(new Parameter(n2)))
{
    set_value(get_pow_fun());
}


std::function<double()> Pow::get_pow_fun() const
{
    return [n1_,n2_,&lambda]()->double{return lambda*(pow(n1_->get_value()(),n2_->get_value()()));};
}

NodePtr Pow::diff(const StatePtr& state) const
{
    //u(x)^v(x)*((diff(v(x), x))*ln(u(x))+v(x)*(diff(u(x), x))/u(x))


    return NodePtr(Mult(new Multiply(PowPtr(new Pow(*this)), SumPtr(new Sum(Mult(new Multiply(n2_->diff(state),LnPtr(new Ln(n2_)))),DividePtr(new Divide(Mult(new Multiply(n1_->diff(state),n2_)),n1_)))))));
}

std::string Pow::get_operator_name() const
{
    return "^";
}

NodePtr Pow::clone() const
{
    return NodePtr(new Pow(*this));
}
