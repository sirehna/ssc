/*
 * NodeSerializationVisitor.cpp
 *
 * \date 28 janv. 2013, 12:42:30
 *  \author cec
 */

#include "NodeSerializationVisitor.hpp"
#include "Multiply.hpp"
#include "Pow.hpp"
#include "State.hpp"

NodeSerializationVisitor::NodeSerializationVisitor(std::ostream& os_): os(os_)
{

}

NodeSerializationVisitor::~NodeSerializationVisitor()
{

}

void NodeSerializationVisitor::visit(const Multiply& node)
{
    auto children = node.get_children();
    if (not(children.empty()))
    {
        const size_t n = children.size();
        for (size_t i = 0 ; i < n-1 ; ++i)
        {
            children.at(i)->accept(*this);
            os << " * ";
        }
        children.at(n-1)->accept(*this);
    }
}

void NodeSerializationVisitor::visit(const Pow& node)
{
    auto child = node.get_child();
    os << "(";
    child->accept(*this);
    os << ")^" << node.get_exponent();
}

void NodeSerializationVisitor::visit(const State& node)
{
    os << node.get_name();
}

void NodeSerializationVisitor::visit(const Parameter& node)
{
    os << node.get_address_string();
}

::std::ostream& operator<<(::std::ostream& os, const Node& node)
{
    NodeSerializationVisitor v(os);
    node.accept(v);
    return os;
}

void NodeSerializationVisitor::parenthezise(const Multiply& node)
{
    node.accept(*this);
}

void NodeSerializationVisitor::parenthezise(const Pow& node)
{
    node.accept(*this);
}

void NodeSerializationVisitor::parenthezise(const State& node)
{
    node.accept(*this);
}

void NodeSerializationVisitor::parenthezise(const Parameter& node)
{
    node.accept(*this);
}
