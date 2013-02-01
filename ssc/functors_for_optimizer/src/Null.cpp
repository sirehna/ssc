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
