/*
 * Serialize.cpp
 *
 * \date 1 f�vr. 2013, 10:09:29
 *  \author cec
 */

#include "ssc/functors_for_optimizer/Serialize.hpp"
#include "ssc/functors_for_optimizer/Binary.hpp"
#include "ssc/functors_for_optimizer/N_ary.hpp"
#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/functors_for_optimizer/Null.hpp"
#include "ssc/functors_for_optimizer/Unary.hpp"
#include "ssc/functors_for_optimizer/Constant.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/functors_for_optimizer/Sum.hpp"

#include <cmath>

Serialize::Serialize(std::ostream& os_) : os(os_), parenthesize_next_node(false)
{

}


void Serialize::visit(const Multiply& node)
{
    auto sons = node.get_sons();
    if (sons.empty())
    {
        os << "0";
    }
    else
    {
        double k = node.get_multiplicative_factor();
        if ((k<0) && (k!=-1)) os << "(" << k << ")*";
        if (k==-1) os << "- ";
        if ((k > 0) && (k!=1)) os << k << "*";

        if (sons.size()==1) sons.front()->accept(*this);
        if (sons.size()>1)
        {
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
}

void Serialize::visit(const Sum& node)
{
    auto sons = node.get_sons();
    if (sons.empty()) os << "0";
    if (sons.size()==1) sons.front()->accept(*this);
    if (sons.size()>1)
    {
        const double k = node.get_multiplicative_factor();
        serialize_multiplicative_factor(k);
        if (parenthesize_next_node || (k!=1)) os << "(";
        bool parenthesize_next_node_back = parenthesize_next_node;
        parenthesize_next_node = false;
        for (size_t i = 0 ; i < sons.size()-1 ; ++i)
        {
            sons.at(i)->accept(*this);
            if (sons.at(i+1)->is_negative())
            {
                os << " ";
            }
            else
            {
                os << " + ";
            }
        }
        sons.back()->accept(*this);
        parenthesize_next_node = parenthesize_next_node_back;
        if (parenthesize_next_node || (k!=1)) os << ")";
    }
}


void Serialize::visit(const Binary& node)
{
    const double k = node.get_multiplicative_factor();
    serialize_multiplicative_factor(k);
    if (k !=1) os << "(";
    auto n1 = node.get_lhs();
    auto n2 = node.get_rhs();
    bool parenthesize_next_node_back = parenthesize_next_node;
    parenthesize_next_node = true;
    /*os << "(";
    serialize_multiplicative_factor(k);
    auto n1 = node.get_lhs();
    auto n2 = node.get_rhs();*/
    n1->accept(*this);
    os << " ";
    os << node.get_operator_name();
    os << " ";
    n2->accept(*this);
    parenthesize_next_node = parenthesize_next_node_back;
    //os << ")";
    if (k !=1) os << ")";
}

void Serialize::serialize_multiplicative_factor(const double& k)
{
    if (parenthesize_next_node && (fabs(k) != 1)) os << "(";
    if ((k > 0) && (k != 1))  os << k << "*";
    if (k == -1)              os << "- ";
    if ((k < 0) && (k != -1)) os << "- " << fabs(k) << " * ";
    if (parenthesize_next_node && (fabs(k) != 1)) os << ")";
    /*if (k == -1)
    {
        os << "- ";
    }
    else if (k == 1)
    {
    }
    else
    {
        if (k < 0)
        {
            os << "- " << fabs(k);
        }
        else
        {
            os << k;
        }
        os << " * ";
    }*/
}
void Serialize::visit(const State& node)
{
    const double k = node.get_multiplicative_factor();
    if ((k < 0) && parenthesize_next_node) os << "(";
    serialize_multiplicative_factor(k);
    os << node.get_name();
    if ((k < 0) && parenthesize_next_node) os << ")";
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
    serialize_multiplicative_factor(node.get_multiplicative_factor());
    os << node.get_operator_name() << "(";
    node.get_son()->accept(*this);
    os << ")";
}

void Serialize::visit(const Constant& node)
{
    const double k = node.get_lambda()();
    if ((k < 0) && parenthesize_next_node) os << "(";
    if (k < 0)      os << "- " << fabs(k);
    else if (k!= 0) os << k;
    if ((k < 0) && parenthesize_next_node) os << ")";
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
