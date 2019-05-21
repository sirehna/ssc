/*
 * StateAndParameterCounter.hpp
 *
 * \date Feb 24, 2016
 * \author cec
 */

#ifndef FUNCTORS_FOR_OPTIMIZER_COUNT_STATES_AND_PARAMETERS_HPP_
#define FUNCTORS_FOR_OPTIMIZER_COUNT_STATES_AND_PARAMETERS_HPP_

#include "ssc/functors_for_optimizer/Node.hpp"
#include "ssc/macros/tr1_macros.hpp"

#include TR1INC(memory)

namespace ssc
{
    namespace functors_for_optimizer
    {
        class StateAndParameterCounter
        {
            public:
                StateAndParameterCounter(const NodePtr& node);
                size_t max_state_index() const;
                size_t max_parameter_index() const;
                bool there_are_states() const;
                bool there_are_parameters() const;

            private:
                StateAndParameterCounter(); // Disabled
                class Impl;
                TR1(shared_ptr)<Impl> pimpl;
        };
    }
}


#endif /* FUNCTORS_FOR_OPTIMIZER_COUNT_STATES_AND_PARAMETERS_HPP_ */
