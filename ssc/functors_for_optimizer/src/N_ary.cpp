/*
 * Binary.cpp
 *
 * \date 31 janv. 2013, 16:06:42
 *  \author cec
 */

#include "ssc/functors_for_optimizer/N_ary.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"
#include "ssc/functors_for_optimizer/Constant.hpp"
#include <algorithm>

#if defined(_MSC_VER)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#define not !
#endif

N_ary::N_ary(const NodePtr& n1, const NodePtr& n2) : sons(std::vector<NodePtr>())
{
    sons.push_back(n1);
    sons.push_back(n2);
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

std::map<NodePtr, size_t> N_ary::get_occurence_of_each_factor() const
{
    std::map < NodePtr, size_t > factor;
    std::vector<NodePtr> simplified_sons;
    for (auto node = sons.begin(); node != sons.end(); ++node)
    {
        simplified_sons.push_back((*node)->simplify());
    }

    for (auto node = simplified_sons.begin(); node != simplified_sons.end(); ++node)
    {
        bool found = false;
        Node* ptr = (*node).get();
        for (auto it = factor.begin(); it != factor.end(); ++it)
        {
            if ((it->first)->equals(*ptr))
            {
                found = true;
                it->second++;
            }
        }

        if (!(found))
        {
            factor[*node] = 1;
        }
    }

    return factor;
}

std::vector<NodePtr> N_ary::group_constants_together(const std::vector<NodePtr>& nodes, const std::function<double(double,double)>& f) const
{
    double constant_term = 0;
    std::vector<NodePtr> ret;
    for (auto node = nodes.begin() ; node != nodes.end() ; ++node)
    {
        if ((*node)->get_type() == "Constant") // TODO: use a visitor for simplifications
        {
            constant_term = f(constant_term,(*node)->get_lambda()());
        }
        else
        {
            ret.push_back(*node);
        }
    }
    if (constant_term != 0) ret.push_back(Constant(constant_term).clone());
    return ret;
}

bool N_ary::is_constant() const
{
    for (auto son = sons.begin() ; son != sons.end() ; ++son)
    {
        if (not((*son)->is_constant())) return false;
    }
    return true;
}

