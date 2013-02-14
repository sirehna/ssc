/*
 * Binary.cpp
 *
 * \date 31 janv. 2013, 16:06:42
 *  \author cec
 */

#include "N_ary.hpp"
#include "NodeVisitor.hpp"
#include "Constant.hpp"
#include <algorithm>

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

std::vector<NodePtr> N_ary::get_sons() const
{
    return sons;
}

bool N_ary::equals(const Node& rhs) const
{
    return rhs.equals_derived(*this);
}

bool N_ary::equals_derived(const N_ary& rhs) const
{
    auto reference = rhs.sons;
    for (auto son1 = sons.begin() ; son1 != sons.end() ; ++son1)
    {
        auto p = std::find (reference.begin(),reference.end(),*son1);
        bool match = p!=reference.end();
        if (not(match)) return false;
        reference.erase(p);
    }
    return true;
}

bool N_ary::equals_derived(const Constant& rhs) const
{
    if (sons.empty()) return rhs.equals_derived(0);
    if (sons.size() == 1) return sons.front()->equals_derived(rhs);
    return false;
}

std::vector<NodePtr> N_ary::extract_subnodes(const std::function<std::vector<NodePtr>(const NodePtr& n)>& extractor)
{
    std::vector<NodePtr> ret;
    for (auto son = sons.begin(); son != sons.end(); ++son)
    {
        const std::vector<NodePtr> subnodes = extractor(*son);
        ret.insert(ret.end(), subnodes.begin(), subnodes.end());
    }
    return ret;
}

void N_ary::update_lambda()
{
    common_build();
}
