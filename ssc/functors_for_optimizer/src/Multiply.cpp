/*
 * Multiply.cpp
 *
 * \date 23 janv. 2013, 08:29:31
 *  \author cec
 */

#include "Multiply.hpp"
#include "Sum.hpp"
#include "NodeVisitor.hpp"
#include "Null.hpp"
#include <algorithm>
#include "FunctorAlgebra.hpp"
#include "Pow.hpp"

Multiply::Multiply(const NodePtr& n1, const NodePtr& n2) : N_ary(n1,n2)
{
    common_build();
}

void Multiply::common_build()
{
    auto factors = [](const NodePtr& n)->std::vector<NodePtr>{return n->get_factors();};
    sons = extract_subnodes(factors);
    remove_ones_and_zeros();

    if (sons.empty())
    {
        set_value([]()->double {return 0;});
    }
    else
    {
        set_value([factor,sons]()->double
                  {
                      double ret = 1;
                      for (auto son = sons.begin() ; son != sons.end() ; ++son)
                      {
                          ret *= (*son)->get_lambda()();
                      }
                      return factor*ret;
                   });
    }
}

void Multiply::remove_ones_and_zeros()
{
    auto equal_to_one = [](NodePtr node)->bool{return node == 1;};
    auto equal_to_zero = [](NodePtr node)->bool{return node->is_null();};
    if (std::any_of(sons.begin(), sons.end(), equal_to_zero)) sons.clear();
    auto new_end = std::remove_if (sons.begin(), sons.end(), equal_to_one );
    sons.erase(new_end,sons.end());
}

Multiply::Multiply(const std::vector<NodePtr>& nodes) : N_ary(nodes)
{
    common_build();
}

bool Multiply::null_or_one(const NodePtr& node) const
{
    return node->is_null() || (node == 1);
}

NodePtr Multiply::diff(const StatePtr& state) const
{
    std::vector<NodePtr> dsons_dstate;
    const size_t n = sons.size();
    if (n==1) return sons.front()->diff(state);
    auto is_null = [](const NodePtr& node){return node->is_null();};
    auto not_equal_to_one = [](const NodePtr& node){return node != 1;};
    if (std::any_of(sons.begin(), sons.end(), is_null)) return NodePtr(new Null());
    for (size_t i = 0 ; i < n ; ++i)
    {
        std::vector<NodePtr> all_sons_except_i = sons;
        all_sons_except_i.erase(all_sons_except_i.begin()+i);
        std::vector<NodePtr> prod = all_sons_except_i;
        auto new_end = std::copy_if(all_sons_except_i.begin(),all_sons_except_i.end(), prod.begin(), not_equal_to_one);
        prod.erase(new_end, prod.end());

        if (sons.at(i)->diff(state) != 1)
        {
            prod.push_back(sons.at(i)->diff(state));
        }
        dsons_dstate.push_back(NodePtr(new Multiply(prod)));
    }
    return NodePtr(new Sum(dsons_dstate));
}

std::string Multiply::get_operator_name() const
{
    return "*";
}

NodePtr Multiply::clone() const
{
    Multiply *ret = new Multiply(sons);
    ret->multiply_by(factor);
    ret->update_lambda();
    return NodePtr(ret);
}

bool Multiply::is_null() const
{
    auto isnull = [](NodePtr son)->double{return son->is_null();};
    if (factor==0)                                     return true;
    if (sons.empty())                                  return true;
    if (std::any_of(sons.begin(), sons.end(), isnull)) return true;
                                                       return false;
}

std::string Multiply::get_type() const
{
    return "Multiply";
}

NodePtr Multiply::simplify() const
{
    const std::map<NodePtr,size_t> factor = get_occurence_of_each_factor();
    std::vector<NodePtr> ret;
    for (auto f = factor.begin() ; f != factor.end() ; ++f)
    {
        const size_t nb_occurences = f->second;
        if (nb_occurences>1)
        {
            ret.push_back(NodePtr(new Pow(f->first->simplify(), nb_occurences)));
        }
        else
        {
            ret.push_back(f->first->simplify());
        }
    }
    return NodePtr(new Multiply(ret));
}
std::vector<NodePtr> Multiply::get_factors() const
{
    return sons;
}

FactorMap Multiply::get_factors_with_exponents() const
{
    FactorMap ret;
    for (auto son = sons.begin() ; son != sons.end() ; ++son)
    {
        //ret += (*son)->get_factors_with_exponents();
    }
    return ret;
}
void Multiply::accept(NodeVisitor& v) const
{
    v.visit(*this);
}
