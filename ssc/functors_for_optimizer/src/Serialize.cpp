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

#include "test_macros.hpp"

Serialize::Serialize(std::ostream& os_) : os(os_)
{

}


void Serialize::visit(const N_ary& node)
{
    auto sons = node.get_sons();
    os << "(";
    for (size_t i = 0 ; i < sons.size()-1 ; ++i)
    {
        sons.at(i)->accept(*this);
        os << " ";
        os << node.get_operator_name();
        os << " ";
    }
    if (not(sons.empty())) sons.back()->accept(*this);
    os << ")";
}

void Serialize::visit(const Binary& node)
{
    COUT("");
    auto n1 = node.get_lhs();
    COUT("");
    auto n2 = node.get_rhs();
    COUT("");
    os << "(";
    COUT("");
    n1->accept(*this);
    COUT("");
    os << " ";
    COUT("");
    os << node.get_operator_name();
    COUT("");
    os << " ";
    COUT("");
    n2->accept(*this);
    COUT("");
    os << ")";
    COUT("");
}

void Serialize::visit(const State& node)
{
    os << node.get_name();
}

void Serialize::visit(const Parameter& node)
{
    os << node.get_value()();
}

void Serialize::visit(const Null& node)
{
    os << node.get_value()();
}

void Serialize::visit(const Unary& node)
{
    os << node.get_operator_name() << "(";
    node.get_son()->accept(*this);
    os << ")";
}

void Serialize::visit(const Constant& node)
{
    os << node.get_value()();
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
