/*
 * GradHes.cpp
 *
 * \date 20 f�vr. 2013, 12:21:18
 *  \author cec
 */

#include "GradHes.hpp"
#include "StateGetter.hpp"
#include "Grad.hpp"
#include "FunctionMatrix.hpp"
#include "State.hpp"
#include "FunctorAlgebra.hpp"
#include "Multiply.hpp"
#include "Sum.hpp"

StateList get_states(const NodePtr& objective_function, const std::vector<NodePtr>& constraints)
{
    StateGetter retrieve_states;
    retrieve_states(objective_function);
    retrieve_states(constraints);
    return retrieve_states.get();
}

StateList get_states(const NodePtr& objective_function)
{
    StateGetter retrieve_states;
    retrieve_states(objective_function);
    return retrieve_states.get();
}

StateList get_states(const std::vector<NodePtr>& constraints)
{
    StateGetter retrieve_states;
    retrieve_states(constraints);
    return retrieve_states.get();
}

void append(StateList& list, const StatePtr& state)
{
    StateGetter retrieve_states(list);
    retrieve_states(state);
    list = retrieve_states.get();
}

Grad grad(const NodePtr& f, const StateList& states)
{
    Grad ret;
    for (auto state = states.begin() ; state != states.end() ; ++state)
    {
        auto df_dstate = f->diff(*state);
        if (not(df_dstate->is_null()))
        {
            ret.index.push_back((*state)->get_index());
            ret.values.push_back(df_dstate->get_lambda());
        }
    }

    return ret;
}

FunctionMatrix hes(const NodePtr& f, const std::vector<NodePtr>& g, const Parameter& sigma_f, const std::vector<Parameter>& lambda, const StateList& states)
{
    FunctionMatrix ret;
    const size_t n = states.size();
    for (size_t i = 0 ; i < n ; ++i)
    {
        auto xi = states.at(i);
        for (size_t j = 0 ; j <= i ; ++j)
        {
            auto xj = states.at(j);
            NodePtr d2f_dxidxj = sigma_f*f->diff(xi)->diff(xj);
            bool d2g_is_null = true;
            for (size_t j = 0 ; j < g.size() ; ++j)
            {
                d2f_dxidxj = d2f_dxidxj + lambda.at(j)*g.at(j)->diff(xi)->diff(xj);
                if (not(g.at(j)->diff(xi)->diff(xj)->is_null())) d2g_is_null = false;
            }
            const bool term_is_zero =  (f->diff(xi)->diff(xj)->is_null()) && d2g_is_null;
            if (not(term_is_zero))
            {
                ret.row_index.push_back((xi)->get_index());
                ret.col_index.push_back((xj)->get_index());
                ret.values.push_back(d2f_dxidxj->get_lambda());
            }
        }
    }
    return ret;
}

FunctionMatrix jac(const std::vector<NodePtr>& g, const StateList& states)
{
    FunctionMatrix ret;
    const size_t n = states.size();
    const size_t m = g.size();
    for (size_t i = 0 ; i < m ; ++i)
    {
        for (size_t j = 0 ; j < n ; ++j)
        {
            const auto xj = states.at(j);
            const auto dgi_dxj = g.at(i)->diff(xj);
            if (not(dgi_dxj->is_null()))
            {
                ret.row_index.push_back(i);
                ret.col_index.push_back(xj->get_index());
                ret.values.push_back(dgi_dxj->get_lambda());
            }
        }
    }
    return ret;
}