/*
 * Sum.cpp
 *
 * \date 31 janv. 2013, 16:05:53
 *  \author cec
 */

#include "Sum.hpp"
#include "NodeVisitor.hpp"
#include <algorithm>
#include "FunctorAlgebra.hpp"

#include "test_macros.hpp"
#include "Serialize.hpp"
Sum::Sum(const NodePtr& n1, const NodePtr& n2) : N_ary(n1,n2)
{
    common_build();
}

Sum::Sum(const std::vector<NodePtr>& nodes) : N_ary(nodes)
{
    common_build();
}

void Sum::common_build()
{
    auto operands = [](const NodePtr& n)->std::vector<NodePtr>{return n->get_operands();};
    for (auto son=sons.begin() ; son != sons.end() ; ++son)
    {
//        COUT(*son);
    }
    sons = extract_subnodes(operands);
    for (auto son=sons.begin() ; son != sons.end() ; ++son)
    {
//        COUT(*son);
    }
    remove_zeros();
    for (auto son=sons.begin() ; son != sons.end() ; ++son)
    {
//        COUT(*son);
    }
    if (sons.empty())
    {
        set_value([]()->double {return 0;});
    }
    else
    {
        set_value([sons,factor]()->double
                      {
                          double ret = 0;
                          for (auto son = sons.begin() ; son != sons.end() ; ++son)
                          {
                            //  COUT(*son);
                              ret += (*son)->get_lambda()();
                          }
                          //COUT(factor);
                          return factor*ret;
                       });
    }
}

void Sum::remove_zeros()
{
    auto equal_to_zero = [](NodePtr node)->bool{return node->is_null();};
    auto new_end = std::remove_if (sons.begin(), sons.end(), equal_to_zero );
    sons = std::vector<NodePtr>(sons.begin(), new_end);
}

NodePtr Sum::diff(const StatePtr& state) const
{
    std::vector<NodePtr> dsons;
    for (auto son = sons.begin() ; son != sons.end() ; ++son)
    {
        auto dson_dstate = (*son)->diff(state);
        if (not(dson_dstate->is_null())) dsons.push_back(dson_dstate);
    }
    return NodePtr(new Sum(dsons));
}

std::string Sum::get_operator_name() const
{
    return "+";
}

NodePtr Sum::clone() const
{
    return NodePtr(new Sum(*this));
}

bool Sum::is_null() const
{
    if (sons.empty()) return true;
    auto is_not_null = [](NodePtr son)->double{return not(son->is_null());};
    if (std::any_of(sons.begin(), sons.end(), is_not_null)) return false;
                                                            return true;
}

std::string Sum::get_type() const
{
    return "Sum";
}

NodePtr Sum::simplify() const
{
    const std::map<NodePtr,size_t> factor = get_occurence_of_each_factor();
    std::vector<NodePtr> ret;
    for (auto f = factor.begin() ; f != factor.end() ; ++f)
    {
        ret.push_back(f->first->simplify());
        ret.back()->multiply_by(f->second);
    }
    return NodePtr(new Sum(ret));
}

std::vector<NodePtr> Sum::get_operands() const
{
    std::vector<NodePtr> ret;
    for (auto son = sons.begin() ; son != sons.end() ; ++son)
    {
        ret.push_back((*son)->clone());
        ret.back()->multiply_by(factor);
        ret.back()->update_lambda();
    }
    return ret;
}

bool Sum::must_parenthesize() const
{
    return true;
}

void Sum::accept(NodeVisitor& v) const
{
    v.visit(*this);
}
