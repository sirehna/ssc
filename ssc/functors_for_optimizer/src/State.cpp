#include "State.hpp"
#include "Parameter.hpp"
#include "Null.hpp"
#include "NodeVisitor.hpp"
#include "Constant.hpp"

State::~State()
{
}

State::State(const std::string& name_, const size_t& index_) : Parameter(0),
                                                               name(name_),
                                                               index(index_)
{
    update_lambda();
}


void State::update_lambda()
{
    value = [factor,ptr]() -> double {return factor*(*ptr);};
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
        return NodePtr(new Constant(factor));
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
    State* ret = new State(*this);
    ret->value = [ret]() -> double {return (ret->factor)*(*(ret->ptr));};
    return NodePtr(ret);
}

bool State::is_null() const
{
    return false;
}

bool State::equals(const Node& rhs) const
{
    return rhs.equals_derived(*this);
}

bool State::equals_derived(const State& rhs) const
{
    return ptr == rhs.ptr;
}

std::string State::get_type() const
{
    return "State";
}

