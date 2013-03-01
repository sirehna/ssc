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
#include "Constant.hpp"


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
    //COUT("_______________")
    //COUT(*this)
    for (auto son = sons.begin() ; son != sons.end() ; ++son)
    {
        //COUT(*son);
    }
    sons = extract_subnodes(operands);
    //COUT("11111111111111111111111111")
    for (auto son = sons.begin() ; son != sons.end() ; ++son)
    {
        //COUT(*son);
    }
    remove_zeros();
    //COUT("22222222222222222222222222")
    for (auto son = sons.begin() ; son != sons.end() ; ++son)
    {
        //COUT(*son);
    }
    if (sons.empty())
    {
        set_value([]()->double {return 0;});
    }
    else
    {
        set_value([sons,factor,this]()->double
                      {
                          double ret = 0;
                          for (auto son = sons.begin() ; son != sons.end() ; ++son)
                          {
                              ret += (*son)->get_lambda()();
                          }
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
        dson_dstate->multiply_by(factor);
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

std::vector<NodePtr> Sum::factorize_operands() const
{
    std::vector < NodePtr > ret;
    const std::map<NodePtr, size_t> factor = get_occurence_of_each_factor();
    for (auto f = factor.begin(); f != factor.end(); ++f)
    {
        ret.push_back(f->first->simplify());
        ret.back()->multiply_by(f->second);
    }
    return ret;
}

NodePtr Sum::simplify() const
{
    std::vector<NodePtr> ret = factorize_operands();
    //ret = group_constants_together(ret, [](const double& a, const double& b)->double{////COUT(a);////COUT(b);return a+b;});
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

void Sum::update_lambda()
{
    common_build();
}
