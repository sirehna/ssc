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

#include "SerializeReversePolish.hpp"
#include "Serialize.hpp"

#if defined(_MSC_VER)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#define not !
#endif

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
        const auto sons_ = sons;
        const auto factor_ = factor;
        set_value([sons_,factor_]()->double
                  {
                      double ret = 1;
                      for (auto son = sons_.begin() ; son != sons_.end() ; ++son)
                      {
                          ret *= (*son)->get_lambda()();
                      }
                      return factor_*ret;
                   });
    }
}

void Multiply::remove_ones_and_zeros()
{
    auto equal_to_one = [](NodePtr node)->bool{return node->equals_one();};
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
    SerializeReversePolish s(std::cout);
    const size_t n = sons.size();
    if (n==1)
    {
        auto dthis_dstate = sons.front()->diff(state);
        dthis_dstate->multiply_by(factor);
        return dthis_dstate;
    }
    const auto is_null = [](const NodePtr& node)->bool{return node->is_null();};
    if (std::any_of(sons.begin(), sons.end(), is_null)) return NodePtr(new Null());
    const auto not_equal_to_one = [](const NodePtr& node)->bool{return node != 1;};
    for (size_t i = 0 ; i < n ; ++i)
    {
        std::vector<NodePtr> all_sons_except_i = sons;
        all_sons_except_i.erase(all_sons_except_i.begin()+i);
        std::vector<NodePtr> prod = all_sons_except_i;
        auto new_end = std::copy_if(all_sons_except_i.begin(),all_sons_except_i.end(), prod.begin(), not_equal_to_one);
        prod.erase(new_end, prod.end());
        auto dson_dstate = sons.at(i)->diff(state);

        if (not(dson_dstate->is_null()))
        {
            prod.push_back(dson_dstate);
            dsons_dstate.push_back(NodePtr(new Multiply(prod)));
        }
    }
    if (std::all_of(dsons_dstate.begin(), dsons_dstate.end(), is_null)) return NodePtr(new Null());
    if (dsons_dstate.size()>1)
    {
        NodePtr dthis_dstate(new Sum(dsons_dstate));
        dthis_dstate->multiply_by(factor);
        return dthis_dstate;
    }
    dsons_dstate.back()->multiply_by(factor);
    return dsons_dstate.back();
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

std::vector<NodePtr> Multiply::group_factors_together() const
{
    std::vector < NodePtr > ret;
    const std::map<NodePtr, size_t> factor = get_occurence_of_each_factor();
    for (auto f = factor.begin(); f != factor.end(); ++f)
    {
        const size_t nb_occurences = f->second;
        if (nb_occurences > 1)
        {
            ret.push_back(
                    NodePtr(new Pow(f->first->simplify(), (double)nb_occurences)));
        } else
        {
            ret.push_back(f->first->simplify());
        }
    }

    return ret;
}

NodePtr Multiply::simplify() const
{
    if (sons.size() == 1) return sons.front()->clone();
    std::vector<NodePtr> ret = group_factors_together();
    //ret = group_constants_together(ret, [](const double& a, const double& b)->double{return a*b;});
    return NodePtr(new Multiply(ret));
}
std::vector<NodePtr> Multiply::get_factors() const
{
    return sons;
}

FactorMap Multiply::get_factors_with_exponents() const
{
    FactorMap ret;
    return ret;
}
void Multiply::accept(NodeVisitor& v) const
{
    v.visit(*this);
}

void Multiply::update_lambda()
{
	common_build();
}

