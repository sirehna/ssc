/*
 * Difference.cpp
 *
 * \date 1 févr. 2013, 09:22:47
 *  \author cec
 */

#include "Difference.hpp"
#include "NodeVisitor.hpp"

Difference::Difference(const NodePtr& n1, const NodePtr& n2) : Binary(n1,n2)
{
    set_value([n1,n2,&lambda]()->double
    {
        return lambda*(n1->get_value()()-n2->get_value()());
    });
}

std::string Difference::get_operator_name() const
{
    return "-";
}

NodePtr Difference::clone() const
{
    return NodePtr(new Difference(*this));
}

NodePtr Difference::diff(const StatePtr& state) const
{
    return NodePtr(new Difference(n1_->diff(state),n2_->diff(state)));
}
