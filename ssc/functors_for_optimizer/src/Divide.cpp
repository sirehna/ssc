/*
 * Divide.cpp
 *
 * \date 1 févr. 2013, 08:59:33
 *  \author cec
 */

#include "Divide.hpp"
#include "State.hpp"
#include "Multiply.hpp"
#include "Difference.hpp"
#include "NodeVisitor.hpp"
#include "Serialize.hpp"
#include "test_macros.hpp"
Divide::Divide(const NodePtr& n1, const NodePtr& n2) : Binary(n1,n2)
{
    set_value([n1_,n2_,&lambda]()->double{return lambda*(n1_->get_value()()/n2_->get_value()());});
}

NodePtr Divide::diff(const StatePtr& state) const
{
    Mult n2_dn1(new Multiply(n2_,n1_->diff(state)));
    Mult n1_dn2(new Multiply(n1_,n2_->diff(state)));
    Mult n2_n2(new Multiply(n2_,n2_));
    DiffPtr s(new Difference(n2_dn1,n1_dn2));
    return NodePtr(new Divide(s,n2_n2));
}

std::string Divide::get_operator_name() const
{
    return "/";
}
