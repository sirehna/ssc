/*
 * Null.cpp
 *
 * \date 29 janv. 2013, 09:40:10
 * \author cec
 */

#include "ssc/functors_for_optimizer/Null.hpp"
#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"

using namespace ssc::functors_for_optimizer;

using namespace ssc::functors_for_optimizer;

Null::Null()
{
    update_lambda();
}

void Null::update_lambda()
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
