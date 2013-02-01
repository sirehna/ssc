/*
 * Sum.cpp
 *
 * \date 31 janv. 2013, 16:05:53
 *  \author cec
 */

#include "Sum.hpp"
#include "NodeVisitor.hpp"

Sum::Sum(const NodePtr& n1, const NodePtr& n2) : Binary(n1,n2)
{
    set_value([n1_,n2_,&lambda]()->double{return lambda*(n1_->get_value()()+n2_->get_value()());});
}

NodePtr Sum::diff(const StatePtr& state) const
{
    return NodePtr(new Sum(n1_->diff(state),n2_->diff(state)));
}

std::string Sum::get_operator_name() const
{
    return "+";
}

NodePtr Sum::clone() const
{
    return NodePtr(new Sum(*this));
}
