/*
 * DiscreteSystem.hpp
 *
 *  Created on: Feb 24, 2021
 *      Author: cady
 */

#ifndef SOLVER_DISCRETESYSTEM_HPP_
#define SOLVER_DISCRETESYSTEM_HPP_

#include <vector>

#include "ssc/solver/ContinuousSystem.hpp"
#include "ssc/solver/Scheduler.hpp"

namespace ssc
{
    namespace solver
    {
        class DiscreteSystem
        {
          public:
            DiscreteSystem(const double dt);
            virtual ~DiscreteSystem() = default;
            /**
             * @brief This is the callback that is called by the scheduler.
             *
             * Updates the discrete states and schedules the next discrete update.
             * @param scheduler Used to get the current time & schedule the next update.
             * @param system This can be used by the 'update' method to retrieve the continuous
             * states of the system.
             */
            void callback(Scheduler &scheduler, ContinuousSystem *system);

            /**
             * @brief Ask the scheduler to call the 'callback' method some time in the future.
             *
             * @param t Time (in seconds) at which the call should be made.
             * @param scheduler Used to schedule the discrete state update.
             */
            void schedule_update(const double t, Scheduler &scheduler);

          private:
            DiscreteSystem();
            /**
             * @brief Get the date of next discrete state update.
             *
             * The default implementation is current_time+constant (most common case), but this
             * behaviour can be overriden. This method will be called by the "callback" public
             * method.
             *
             * @param current_time Current simulation time, in seconds.
             * @return Date at which "callback" will be called (in seconds).
             */
            virtual double get_date_of_next_update(const double current_time) const;

            /**
             * @brief Update the discrete states.
             *
             * This method will be called by the public "callback" method.
             * @param time Current simulation time (in seconds).
             * @param system The continuous system. Used to retrieve the continuous states.
             */
            virtual void update_discrete_states(const double time, ContinuousSystem *system) = 0;

            double dt;
        };
    }
}

#endif /* SOLVER_DISCRETESYSTEM_HPP_ */
