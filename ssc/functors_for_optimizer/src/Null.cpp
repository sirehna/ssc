/*
 * Null.cpp
 *
 * \date 29 janv. 2013, 09:40:10
 *  \author cec
 */

#include "Null.hpp"
#include "State.hpp"
#include "NodeVisitor.hpp"

Null::Null()
{
    value = []()->double {return 0;};
}

NodePtr Null::diff(const StatePtr& state) const
{
    if (state->get_index()) {}
    return NodePtr(new Null());
}

void Null::accept(NodeVisitor& v) const
{
    v.visit(*this);
}

NodePtr Null::clone() const
{
    return NodePtr(new Null(*this));
}

bool Null::is_null() const
{
    return true;
}

bool Null::equals(const Node& rhs) const
{
    return rhs.equals_derived(*this);
}

bool Null::equals_derived(const Null& rhs) const
{
    (void) rhs;
    return true;
}

std::string Null::get_type() const
{
    return "Null";
}

bool Null::is_constant() const
{
    return true;
}
