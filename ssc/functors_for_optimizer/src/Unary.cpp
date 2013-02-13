/*
 * Unary.cpp
 *
 * \date 1 févr. 2013, 12:34:31
 *  \author cec
 */

#include "Unary.hpp"
#include "NodeVisitor.hpp"

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
