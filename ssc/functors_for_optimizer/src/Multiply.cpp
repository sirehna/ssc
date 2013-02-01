/*
 * Multiply.cpp
 *
 * \date 23 janv. 2013, 08:29:31
 *  \author cec
 */

#include "Multiply.hpp"
#include "Sum.hpp"
#include "NodeVisitor.hpp"

Multiply::Multiply(const NodePtr& n1, const NodePtr& n2) : Binary(n1,n2)
{
    set_value([&n1_,&n2_,&lambda]()->double{return lambda*(n1_->get_value()()*n2_->get_value()());});
}

NodePtr Multiply::diff(const StatePtr& state) const
{
    return NodePtr(new Sum(Mult(new Multiply(n1_->diff(state),n2_)),Mult(new Multiply(n2_->diff(state),n1_))));
}

std::string Multiply::get_operator_name() const
{
    return "*";
}
