/*
 * Binary.cpp
 *
 * \date 31 janv. 2013, 16:06:42
 *  \author cec
 */

#include "N_ary.hpp"
#include "NodeVisitor.hpp"

N_ary::N_ary(const NodePtr& n1, const NodePtr& n2) : sons({n1,n2})
{
}

N_ary::N_ary(const std::vector<NodePtr>& nodes) : sons(nodes)
{

}

void N_ary::set_value(const std::function<double()>& val)
{
    value = val;
}

void N_ary::accept(NodeVisitor& v) const
{
    v.visit(*this);
}

std::vector<NodePtr> N_ary::get_sons() const
{
    return sons;
}
