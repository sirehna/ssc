/*
 * Node.cpp
 *
 * \date 29 janv. 2013, 15:32:23
 *  \author cec
 */


#include "Node.hpp"
#include "Constant.hpp"
#include "Cos.hpp"
#include "Difference.hpp"
#include "Divide.hpp"
#include "Ln.hpp"
#include "Multiply.hpp"
#include "Null.hpp"
#include "Parameter.hpp"
#include "Pow.hpp"
#include "Sin.hpp"
#include "State.hpp"
#include "Sum.hpp"


Node::Node() : factor(1), value([](){return 0.;})
{
    const auto factor_ = factor;
    value = [factor_]()->double{return factor_;};
}

std::function<double()> Node::get_lambda() const
{
    return value;
}

void Node::multiply_by(const double& k)
{
    factor *= k;
    update_lambda();
}

bool Node::is_negative() const
{
    return factor<0;
}

bool Node::equals_derived(const Constant& rhs) const
{
    (void)rhs; // Silence "unused parameter" warning
    return false;
}

bool Node::equals_derived(const Unary& rhs) const
{
    (void)rhs; // Silence "unused parameter" warning
    return false;
}

bool Node::equals_derived(const Difference& rhs) const
{
    (void)rhs; // Silence "unused parameter" warning
    return false;
}

bool Node::equals_derived(const Null& rhs) const
{
    (void)rhs; // Silence "unused parameter" warning
    return false;
}

bool Node::equals_derived(const Parameter& rhs) const
{
    (void)rhs; // Silence "unused parameter" warning
    return false;
}

bool Node::equals_derived(const Pow& rhs) const
{
    (void)rhs; // Silence "unused parameter" warning
    return false;
}

bool Node::equals_derived(const N_ary& rhs) const
{
    (void)rhs; // Silence "unused parameter" warning
    return false;
}

bool Node::equals_derived(const Divide& rhs) const
{
    (void)rhs; // Silence "unused parameter" warning
    return false;
}

bool Node::equals_derived(const State& rhs) const
{
    (void)rhs; // Silence "unused parameter" warning
    return false;
}

NodePtr Node::simplify() const
{
    return clone();
}

FactorMap Node::get_factors_with_exponents() const
{
    NodePtr n = clone();
    n->update_lambda();
    std::map<NodePtr,NodePtr> ret;
    ret[n] = Constant(1).clone();
    return ret;
}

std::vector<NodePtr> Node::get_operands() const
{
    NodePtr p = clone();
    p->update_lambda();
    return std::vector<NodePtr>(1,p);
}

std::vector<NodePtr> Node::get_factors() const
{
    return std::vector<NodePtr>(1,clone());
}


double Node::get_multiplicative_factor() const
{
    return factor;
}

bool Node::must_parenthesize() const
{
    return true;
}

void Node::update_lambda()
{
}

bool Node::equals_one() const
{
    if (not(is_constant())) return false;
    return (get_lambda()() == 1);
}

bool Node::is_constant() const
{
    return false;
}
