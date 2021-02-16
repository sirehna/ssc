/*
 * DefaultScheduler.hpp
 *
 * \date 21 mars 2014
 *      Author: cec
 */

#ifndef DEFAULTSCHEDULER_HPP_
#define DEFAULTSCHEDULER_HPP_

#include <list>

namespace ssc
{
    namespace solver
    {
        class DefaultScheduler
        {
            public:
                DefaultScheduler(const double tstart, const double tend_, const double dt)
                        : current_time(tstart)
                        , scheduled_time_events()
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

                void add_time_event(const double t)
                {
                    if (t <=tend)
                    {
                        scheduled_time_events.push_back(t);
                        scheduled_time_events.sort();
                    }
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
                DefaultScheduler();
                double current_time;
                std::list<double> scheduled_time_events;
                double tend;
        };
    }
}

#endif /* DEFAULTSCHEDULER_HPP_ */
