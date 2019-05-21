/*
 * GradHes.hpp
 *
 * \date 20 févr. 2013, 12:21:08
 * \author cec
 */

#ifndef GRADHES_HPP_
#define GRADHES_HPP_

#include "Grad.hpp"
#include "FunctionMatrix.hpp"
#include "ssc/macros/tr1_macros.hpp"
#include TR1INC(memory)
#include <vector>

namespace ssc
{
    namespace functors_for_optimizer
    {
        class State;
        class Node;
        class Parameter;
        typedef TR1(shared_ptr)<Node> NodePtr;
        typedef TR1(shared_ptr)<State> StatePtr;

        typedef std::vector<StatePtr> StateList;

        StateList get_states(const NodePtr& objective_function, const std::vector<NodePtr>& constraints);
        StateList get_states(const NodePtr& objective_function);
        StateList get_states(const std::vector<NodePtr>& constraints);
        void append(StateList& list, const StatePtr& state);
        template <typename T> Grad<T> grad(const NodePtr& f, const StateList& states);
        template <> Grad<std::function<double()> > grad(const NodePtr& f, const StateList& states);
        template <typename T> FunctionMatrix<T> hes(const NodePtr& f, const std::vector<NodePtr>& g, const Parameter& sigma_f, const std::vector<Parameter>& lambda, const StateList& states);
        template <> FunctionMatrix<std::function<double()> > hes(const NodePtr& f, const std::vector<NodePtr>& g, const Parameter& sigma_f, const std::vector<Parameter>& lambda, const StateList& states);
        template <typename T> FunctionMatrix<T> jac(const std::vector<NodePtr>& g, const StateList& states);
        template <> FunctionMatrix<std::function<double()> > jac(const std::vector<NodePtr>& g, const StateList& states);
    }
}

#endif /* GRADHES_HPP_ */
