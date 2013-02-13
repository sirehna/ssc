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

Node::Node() : lambda(1), value([&lambda]()->double{return lambda;})
{

}

std::function<double()> Node::get_value() const
{
    return value;
}

void Node::multiply_by(const double& k)
{
    lambda *= k;
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
