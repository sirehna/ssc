/*
 * StateGetter.cpp
 *
 * \date 20 févr. 2013, 12:53:19
 *  \author cec
 */

#include "StateGetter.hpp"
#include "Binary.hpp"
#include "N_ary.hpp"
#include "State.hpp"
#include "Null.hpp"
#include "Unary.hpp"
#include "Constant.hpp"
#include "Multiply.hpp"
#include "Sum.hpp"
#include "State.hpp"
#include <set>
#include <algorithm>

class StateGetter::StateGetter_pimpl
{
    public:
        StateGetter_pimpl() : states(std::set<State>()){}
        std::vector<StatePtr> get_states() const
        {
            return sort_states(get_unsorted_vector_of_states());
        }

        void add_state(const State& state)
        {
            states.insert(state);
        }

    private:
        std::vector<StatePtr> sort_states(std::vector<StatePtr> ret) const
        {
            std::sort(ret.begin(), ret.end(), [](const StatePtr lhs, const StatePtr& rhs)->bool
                                              {
                                                  return lhs->get_index()<rhs->get_index();
                                              });
            return ret;
        }

        std::vector<StatePtr> get_unsorted_vector_of_states() const
        {
            std::vector<StatePtr> ret;
            for (auto s = states.begin() ; s != states.end() ; ++s)
            {
                ret.push_back(StatePtr(new State(*dynamic_cast<State*>(s->clone().get()))));
            }
            return ret;
        }

        std::set<State> states;
};

StateGetter::StateGetter() : pimpl(new StateGetter_pimpl())
{
}

StateGetter::StateGetter(const StateList& list) : pimpl(new StateGetter_pimpl())
{
    for (auto l = list.begin() ; l != list.end() ; ++l)
    {
        (*l)->accept(*this);
    }
}


void StateGetter::operator()(const NodePtr& f)
{
    f->accept(*this);
}

void StateGetter::operator()(const std::vector<NodePtr>& g)
{
    for (auto node = g.begin() ; node != g.end() ; ++node)
    {
        operator()(*node);
    }
}

std::vector<StatePtr> StateGetter::get() const
{
    return pimpl->get_states();
}

void StateGetter::visit(const Binary& node)
{
    node.get_lhs()->accept(*this);
    node.get_rhs()->accept(*this);
}

void StateGetter::visit(const Multiply& node)
{
    auto sons = node.get_sons();
    for (auto son = sons.begin() ; son != sons.end() ; ++son)
    {
        (*son)->accept(*this);
    }
}

void StateGetter::visit(const Sum& node)
{
    auto sons = node.get_sons();
    for (auto son = sons.begin() ; son != sons.end() ; ++son)
    {
        (*son)->accept(*this);
    }
}

void StateGetter::visit(const State& node)
{
    pimpl->add_state(*dynamic_cast<State*>(node.clone().get()));
}

void StateGetter::visit(const Parameter& node)
{
    (void)node;
}

void StateGetter::visit(const Null& node)
{
    (void)node;
}

void StateGetter::visit(const Unary& node)
{
    node.get_son()->accept(*this);
}

void StateGetter::visit(const Constant& node)
{
    (void)node;
}
