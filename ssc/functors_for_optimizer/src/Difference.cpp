/*
 * Difference.cpp
 *
 * \date 1 févr. 2013, 09:22:47
 *  \author cec
 */

#include "Difference.hpp"
#include "NodeVisitor.hpp"

Difference::Difference(const NodePtr& n1, const NodePtr& n2) : Sum(n1,n2)
{
    n2_->multiply_by(-1);
}

std::string Difference::get_operator_name() const
{
    return "-";
}
