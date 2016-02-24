/*
 * count_states_and_parameters.hpp
 *
 *  Created on: Feb 24, 2016
 *      Author: cady
 */

#ifndef FUNCTORS_FOR_OPTIMIZER_COUNT_STATES_AND_PARAMETERS_HPP_
#define FUNCTORS_FOR_OPTIMIZER_COUNT_STATES_AND_PARAMETERS_HPP_

#include "ssc/functors_for_optimizer/Node.hpp"

namespace ssc
{
    namespace functors_for_optimizer
    {
        size_t max_state_index(const NodePtr& node);
        size_t max_parameter_index(const NodePtr& node);
        bool there_are_states(const NodePtr& node);
        bool there_are_parameters(const NodePtr& node);
    }
}


#endif /* FUNCTORS_FOR_OPTIMIZER_COUNT_STATES_AND_PARAMETERS_HPP_ */
