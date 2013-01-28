#include "State.hpp"
#include <iostream>
#include "NodeAbstractVisitor.hpp"

State::State(const std::string& name_, const size_t& index_) : Parameter(0), name(name_), index(index_)
{
     df.idx.push_back(index);
     df.values.push_back(ValType([]()->double{return 1;}));
}


bool State::operator<(const State& rhs) const
{
    return index<rhs.index;
}

::std::ostream& operator<<(::std::ostream& os, const State& bar)
{
    os << "state: {name: "
       << bar.get_name()
       << ", index: "
       << bar.get_index()
       << ", value: "
       << *bar
       << "}";
    return os;
}

std::string State::get_name() const
{
    return name;
}

size_t State::get_index() const
{
    return index;
}

Grad State::grad() const
{
    return df;
}

Hes State::hes() const
{
    return d2f;
}

void State::accept(NodeAbstractVisitor& v) const
{
    v.visit(*this);
}

Node* State::clone() const
{
    return new State(*this);
}
