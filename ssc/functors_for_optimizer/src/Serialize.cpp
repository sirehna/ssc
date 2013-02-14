/*
 * Serialize.cpp
 *
 * \date 1 févr. 2013, 10:09:29
 *  \author cec
 */

#include "Serialize.hpp"
#include "Binary.hpp"
#include "N_ary.hpp"
#include "State.hpp"
#include "Null.hpp"
#include "Unary.hpp"
#include "Constant.hpp"
#include "Multiply.hpp"
#include "Sum.hpp"


#include <cmath>
#include "test_macros.hpp"

Serialize::Serialize(std::ostream& os_) : os(os_), parenthesize_next_node(false)
{

}


void Serialize::visit(const Multiply& node)
{
    auto sons = node.get_sons();
    if (sons.empty()) os << "0";
    if (sons.size()==1) sons.front()->accept(*this);
    if (sons.size()>1)
    {
        const double k = node.get_multiplicative_factor();
        if ((k<0) && (k!=-1)) os << "(" << k << ")*";
        if (k==-1) os << "- ";
        if ((k > 0) && (k!=1)) os << k << "*";
        bool parenthesize_next_node_back = parenthesize_next_node;
        parenthesize_next_node = true;
        for (size_t i = 0 ; i < sons.size()-1 ; ++i)
        {
            sons.at(i)->accept(*this);
            os << " * ";
        }
        sons.back()->accept(*this);
        parenthesize_next_node = parenthesize_next_node_back;
    }
}

void Serialize::visit(const Sum& node)
{
    auto sons = node.get_sons();
    if (sons.empty()) os << "0";
    if (sons.size()==1) sons.front()->accept(*this);
    if (sons.size()>1)
    {
        const double k = node.get_multiplicative_factor();
        if ((k<0) && (k!=-1)) os << "(" << k << ")*";
        if (k==-1) os << "- ";
        if ((k > 0) && (k!=1)) os << k << "*";
        if (parenthesize_next_node || (k!=1)) os << "(";
        for (size_t i = 0 ; i < sons.size()-1 ; ++i)
        {
            sons.at(i)->accept(*this);
            if (sons.at(i+1)->get_multiplicative_factor()<0)
            {
                os << " ";
            }
            else
            {
                os << " + ";
            }
        }
        sons.back()->accept(*this);
        if (parenthesize_next_node || (k!=1)) os << ")";
    }
}


void Serialize::visit(const Binary& node)
{
    auto n1 = node.get_lhs();
    auto n2 = node.get_rhs();
    parenthesize_next_node = true;
    n1->accept(*this);
    os << " ";
    os << node.get_operator_name();
    os << " ";
    n2->accept(*this);
    parenthesize_next_node = false;
}

void Serialize::visit(const State& node)
{
    const double k = node.get_multiplicative_factor();
    if ((k<0) && parenthesize_next_node) os << "(";
    if ((k>0) && (k!= 1))
    {
        os << k << "*";
    }
    if (k == -1) os << "- ";
    if ((k<0) && (k!=-1)) os << "- " << fabs(k) << "*";
    os << node.get_name();
    if ((k<0) && parenthesize_next_node) os << ")";
}

void Serialize::visit(const Parameter& node)
{
    os << node.get_lambda()();
}

void Serialize::visit(const Null& node)
{
    os << node.get_lambda()();
}

void Serialize::visit(const Unary& node)
{
    os << node.get_operator_name() << "(";
    node.get_son()->accept(*this);
    os << ")";
}

void Serialize::visit(const Constant& node)
{
    os << node.get_lambda()();
}

::std::ostream& operator<<(::std::ostream& os, const Node& node)
{
    Serialize v(os);
    node.accept(v);
    return os;
}

::std::ostream& operator<<(::std::ostream& os, const NodePtr& node)
{
    return (os << *node);
}
