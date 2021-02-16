/*
 * DefaultScheduler.hpp
 *
 * \date 21 mars 2014
 *      Author: cec
 */

#ifndef DEFAULTSCHEDULER_HPP_
#define DEFAULTSCHEDULER_HPP_

namespace ssc
{
    namespace solver
    {
        class DefaultScheduler
        {
            public:
                DefaultScheduler(const double t0_, const double tend_, const double dt_) : current_time(t0_), tstart(t0_), tend(tend_), dt(dt_), i(0) {}

                bool has_more_time_events() const
                {
                    return tend > current_time;
                }

                void add_time_event(const double t_)
                {
                    current_time = t_;
                }

                double get_time() const
                {
                    return current_time;
                }

                double get_step() const
                {
                    return dt;
                }

            private:
                DefaultScheduler();
                double current_time;
                double tstart;
                double tend;
                double dt;
                int i;
        };
    }
}

#endif /* DEFAULTSCHEDULER_HPP_ */
