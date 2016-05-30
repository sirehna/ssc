/*
 * Binary.cpp
 *
 * \date 31 janv. 2013, 16:06:42
 *  \author cec
 */

#include "ssc/functors_for_optimizer/Binary.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"

using namespace ssc::functors_for_optimizer;

Binary::Binary(const NodePtr& n1, const NodePtr& n2) : n1_(n1),n2_(n2)
{
}

NodePtr Binary::get_lhs() const
{
    return n1_;
}

NodePtr Binary::get_rhs() const
{
    return n2_;
}

void Binary::set_value(const std::function<double()>& val)
{
    value = val;
}

