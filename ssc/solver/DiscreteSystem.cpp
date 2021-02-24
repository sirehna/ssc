#include "ssc/solver/DiscreteSystem.hpp"

void ssc::solver::DiscreteSystem::schedule_update(const double t, Scheduler<ContinuousSystem> &scheduler)
{
    Scheduler<ContinuousSystem>::Callback binded_callback = std::bind(
        &DiscreteSystem::callback, this, std::placeholders::_1, std::placeholders::_2);
    scheduler.schedule_discrete_state_update(t, binded_callback);
}

void ssc::solver::DiscreteSystem::callback(Scheduler<ContinuousSystem> &scheduler,
                                           ContinuousSystem &system)
{
    const double tcurrent = scheduler.get_time();
    update_discrete_states(tcurrent, system);
    const double tnext = get_date_of_next_update(tcurrent);
    schedule_update(tnext, scheduler);
}
