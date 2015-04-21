/*
 * Unary.cpp
 *
 * \date 1 f�vr. 2013, 12:34:31
 *  \author cec
 */

#include "ssc/functors_for_optimizer/Unary.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"

using namespace ssc::functors_for_optimizer;

Unary::Unary(const NodePtr& n_) : n(n_)
{
}

NodePtr Unary::get_son() const
{
    return n;
}

void Unary::accept(NodeVisitor& v) const
{
    v.visit(*this);
}

void Unary::set_value(const std::function<double()>& val)
{
    value = val;
}

bool Unary::equals(const Node& rhs) const
{
     return rhs.equals_derived(*this);
}

bool Unary::equals_derived(const Unary& rhs) const
{
    return n->equals(*rhs.n);
}

bool Unary::is_constant() const
{
    return n->is_constant();
}

