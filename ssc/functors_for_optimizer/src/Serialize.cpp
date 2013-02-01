/*
 * Serialize.cpp
 *
 * \date 1 févr. 2013, 10:09:29
 *  \author cec
 */

#include "Serialize.hpp"
#include "Binary.hpp"
#include "State.hpp"
#include "Null.hpp"
#include "Unary.hpp"

Serialize::Serialize(std::ostream& os_) : os(os_)
{

}


void Serialize::visit(const Binary& node)
{
    os << "(";
    node.get_lhs()->accept(*this);
    os << " ";
    os << node.get_operator_name();
    os << " ";
    node.get_rhs()->accept(*this);
    os << ")";
}

void Serialize::visit(const State& node)
{
    os << node.get_name();
}

void Serialize::visit(const Constant& node)
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
