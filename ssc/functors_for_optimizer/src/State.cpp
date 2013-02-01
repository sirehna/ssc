#include "State.hpp"
#include "Constant.hpp"
#include "Null.hpp"
#include "NodeVisitor.hpp"
#include <iostream>
#include "test_macros.hpp"

State::~State()
{
}

State::State(const std::string& name_, const size_t& index_) : Constant(0),
                                                               name(name_),
                                                               index(index_)
{
    value = [&lambda,ptr]() -> double {return lambda*(*ptr);};
}


bool State::operator<(const State& rhs) const
{
    return index<rhs.index;
}

std::string State::get_name() const
{
    return name;
}

size_t State::get_index() const
{
    return index;
}

NodePtr State::diff(const StatePtr& state) const
{
    if (*state==*this)
    {
        return NodePtr(new Constant(lambda));
    }
    else
    {
        return NodePtr(new Null);
    }
}

void State::accept(NodeVisitor& v) const
{
    v.visit(*this);
}
NodePtr State::clone() const
{
    return NodePtr(new State(*this));
}
