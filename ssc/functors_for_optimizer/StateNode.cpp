#include "StateNode.hpp"
#include "State.hpp"


#include <iostream>
#define QUOTE_ME(a) #a
#define QUOTE(a) QUOTE_ME(a)
#define COUT(a) std::cout << "in file " << __FILE__ << ", line " << __LINE__ << ": " << QUOTE(a) << " = " << a << std::endl;


StateNode::StateNode(const State& state) : f([&]()->double {return *state;}),
df(Grad()),
d2f(Hes())
{
    df.idx.push_back(state.get_index());
    df.values.push_back([&]()->double{COUT("lmkj");return 1;});
}


ValType StateNode::val() const
{
    return f;
}

Grad StateNode::grad() const
{
    return df;
}

Hes StateNode::hes() const
{
    return d2f;
}

