/*
 * GradHes.hpp
 *
 * \date 20 févr. 2013, 12:21:08
 *  \author cec
 */

#ifndef GRADHES_HPP_
#define GRADHES_HPP_

#include <vector>
#include <tr1/memory>

class State;
class Node;
typedef std::tr1::shared_ptr<Node> NodePtr;
typedef std::tr1::shared_ptr<State> StatePtr;

typedef std::vector<StatePtr> StateList;


StateList get_states(const NodePtr& objective_function, const std::vector<NodePtr>& constraints);

#endif /* GRADHES_HPP_ */
