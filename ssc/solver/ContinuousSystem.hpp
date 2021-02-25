/*
 * ContinuousSystem.hpp
 *
 *  Created on: Feb 17, 2021
 *      Author: cady
 */

#ifndef SOLVER_CONTINUOUSSYSTEM_HPP_
#define SOLVER_CONTINUOUSSYSTEM_HPP_

#include <vector>

namespace ssc
{
    namespace solver
    {
        class ContinuousSystem
        {
          public:
            ContinuousSystem()
                : state()
            {
            }
            virtual ~ContinuousSystem() = default;
            virtual void operator()(const std::vector<double> &x, std::vector<double> &dx_dt,
                                    const double t)
                = 0;
            /**
             * @brief Sets the state vector to predefined values.
             *
             * By default, doesn't do anything: it's up to each system to decide how to handle this.
             * We guarantee that this function is called after a (successful) integration step.
             *
             * @param x Original states vector (can be modified)
             * @param t Current simulation time (in seconds)
             */
            virtual void force_states(std::vector<double> &, const double) const {}
            std::vector<double> state;
        };
    }
}

#endif /* SOLVER_CONTINUOUSSYSTEM_HPP_ */
