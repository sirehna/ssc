/*
 * Binary.cpp
 *
 * \date 31 janv. 2013, 16:06:42
 *  \author cec
 */

#include "Binary.hpp"
#include "NodeVisitor.hpp"

Binary::Binary(const NodePtr& n1, const NodePtr& n2) : n1_(n1), n2_(n2)
{

}

void Binary::set_value(const std::function<double()>& val)
{
    value = val;
}

NodePtr Binary::get_lhs() const
{
    return n1_;
}

NodePtr Binary::get_rhs() const
{
    return n2_;
}

void Binary::accept(NodeVisitor& v) const
{
    v.visit(*this);
}
