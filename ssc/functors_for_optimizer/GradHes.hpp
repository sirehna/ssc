/*
 * GradHes.hpp
 *
 * \date 20 f�vr. 2013, 12:21:08
 *  \author cec
 */

#ifndef GRADHES_HPP_
#define GRADHES_HPP_

#include <vector>
#include "ssc/macros/tr1_macros.hpp"
#include TR1INC(memory)

class State;
class Node;
class Grad;
class Parameter;
class FunctionMatrix;
typedef TR1(shared_ptr)<Node> NodePtr;
typedef TR1(shared_ptr)<State> StatePtr;

typedef std::vector<StatePtr> StateList;

StateList get_states(const NodePtr& objective_function, const std::vector<NodePtr>& constraints);
StateList get_states(const NodePtr& objective_function);
StateList get_states(const std::vector<NodePtr>& constraints);
void append(StateList& list, const StatePtr& state);
Grad grad(const NodePtr& f, const StateList& states);
FunctionMatrix hes(const NodePtr& f, const std::vector<NodePtr>& g, const Parameter& sigma_f, const std::vector<Parameter>& lambda, const StateList& states);
FunctionMatrix jac(const std::vector<NodePtr>& g, const StateList& states);

#endif /* GRADHES_HPP_ */
