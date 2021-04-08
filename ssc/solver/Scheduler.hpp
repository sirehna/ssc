/*
 * DefaultScheduler.hpp
 *
 * \date 21 mars 2014
 *      Author: cec
 */

#ifndef DEFAULTSCHEDULER_HPP_
#define DEFAULTSCHEDULER_HPP_

#include <functional>
#include <list>
#include <vector>

namespace ssc
{
    namespace solver
    {
        class Scheduler
        {
            public:
                typedef std::function<void(const double t, const std::vector<double>& x)> Callback;
                Scheduler(const double tstart, const double tend_, const double dt)
                        : current_time(tstart)
                        , scheduled_time_events()
                        , discrete_state_updaters()
                        , tend(tend_)
                {
                    if (dt > 0)
                    {
                        double t = tstart;
                        size_t i = 0;
                        while (t+dt < tend)
                        {
                            t = tstart + ((double)(++i))*dt;
                            scheduled_time_events.push_back(t);
                        }
                        scheduled_time_events.push_back(tend);
                        scheduled_time_events.sort();
                    }
                }

                bool has_more_time_events() const
                {
                    return not(scheduled_time_events.empty());
                }

                /**
                 * @brief Get the discrete state updaters to run & remove them from list.
                 *
                 * @return Callbacks to run to update the discrete states (e.g. one updater per controller).
                 */
                std::vector<Callback> get_discrete_state_updaters_to_run()
                {
                    std::vector<Callback> updaters_to_run;
                    std::vector<std::pair<double, Callback> > remaining_updaters;
                    remaining_updaters.reserve(discrete_state_updaters.size());
                    for (const auto t_updater:discrete_state_updaters)
                    {
                        if (t_updater.first <= current_time) // Need to run updater
                        {
                            updaters_to_run.push_back(t_updater.second);
                        }
                        else // Add updater to the list of updaters to keep
                        {
                            remaining_updaters.push_back(t_updater);
                        }
                    }
                    // Only keep selected updaters, discard the rest
                    discrete_state_updaters = remaining_updaters;
                    return updaters_to_run;
                }

                void add_time_event(const double t)
                {
                    if (t <=tend)
                    {
                        scheduled_time_events.push_back(t);
                        scheduled_time_events.sort();
                    }
                }

                void schedule_discrete_state_update(const double t, const Callback& updater)
                {
                    discrete_state_updaters.push_back(std::make_pair(t, updater));
                }

                void advance_to_next_time_event()
                {
                    if (not(scheduled_time_events.empty()))
                    {
                        current_time = scheduled_time_events.front();
                        scheduled_time_events.pop_front();
                    }
                }

                double get_time() const
                {
                    return current_time;
                }

                double get_step() const
                {
                    if (not(scheduled_time_events.empty()))
                    {
                        const double next_time = scheduled_time_events.front();
                        return next_time - current_time;
                    }
                    return 0;
                }

            private:
                Scheduler();
                double current_time;
                std::list<double> scheduled_time_events;
                std::vector<std::pair<double, Callback> > discrete_state_updaters;
                double tend;
        };
    }
}

#endif /* DEFAULTSCHEDULER_HPP_ */
