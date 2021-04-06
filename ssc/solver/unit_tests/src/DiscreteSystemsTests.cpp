/*
 * ODEintTests.cpp
 *
 * \date February 23 2021
 *      Author: CEC
 */

#include "DiscreteSystemsTests.hpp"

#include "ssc/solver/DiscreteSystem.hpp"
#include "ssc/solver/Observers.hpp"
#include "ssc/solver/Scheduler.hpp"
#include "ssc/solver/solve.hpp"
#include "test_systems.hpp"
#include <functional> // Otherwise CLang issues an error (bind.hpp:36:14: error: ‘std::bind’ has not been declared)

#include <boost/numeric/odeint/stepper/euler.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4.hpp>

#include <sstream>

DiscreteSystemsTests::DiscreteSystemsTests()
    : a(ssc::random_data_generator::DataGenerator(36))
{
}

DiscreteSystemsTests::~DiscreteSystemsTests() {}

void DiscreteSystemsTests::SetUp() {}

void DiscreteSystemsTests::TearDown() {}

typedef boost::numeric::odeint::euler<StateType> EulerStepper;
typedef boost::numeric::odeint::runge_kutta4<StateType> RungeKuttaStepper;

struct ContinuousSystem : public ssc::solver::ContinuousSystem
{
    ContinuousSystem(const std::vector<double> &x0) { state = x0; }

    void operator()(const std::vector<double> &, std::vector<double> &dx_dt, double)
    {
        dx_dt[0] = 1;
    }

    void initialize_system_outputs_before_first_observation() {}
    void set_discrete_state(const std::string &, const double) {}
    double get_input_value(const std::string &) const { return -1; }
    double get_state_value(const std::string &) const { return -1; }
};

class DiscreteSystem : public ssc::solver::DiscreteSystem
{
  public:
    DiscreteSystem(const double tstart_, const double dt_)
        : ssc::solver::DiscreteSystem(tstart_, dt_)
        , ticks({ 13 })
        , calltimes()
    {
    }
    std::vector<size_t> ticks;
    std::vector<double> calltimes;

  private:
    void update_discrete_states(const double t, ssc::solver::ContinuousSystem *) override
    {
        ticks.push_back(ticks.back() + 1);
        calltimes.push_back(t);
    }
};

TEST_F(DiscreteSystemsTests, can_initialize_discrete_states)
{
    ssc::solver::VectorObserver observer;
    const double t0 = 6;
    const double dt = 2;
    ssc::solver::Scheduler scheduler(t0, t0 + 4 * dt, dt);
    ContinuousSystem continuous_system(std::vector<double>(1, 0));
    DiscreteSystem discrete_system(t0, dt / 2);
    discrete_system.initialize(scheduler, &continuous_system);
    // Check discrete_system has been initialized
    ASSERT_EQ(std::vector<double>({ t0 }), discrete_system.calltimes);
    ASSERT_EQ(14, discrete_system.ticks.back());
    // Scheduler is still at t=t0, no discrete state updaters left to run.
    ASSERT_EQ(t0, scheduler.get_time());
    ASSERT_EQ(0, scheduler.get_discrete_state_updaters_to_run().size());
    // Discrete system callback has been added to the scheduler.
    scheduler.advance_to_next_time_event();
    ASSERT_EQ(t0 + dt / 2, scheduler.get_time());
    ASSERT_EQ(1, scheduler.get_discrete_state_updaters_to_run().size());
}

TEST_F(DiscreteSystemsTests, one_second_steps)
{
    ssc::solver::VectorObserver observer;
    ContinuousSystem system(std::vector<double>(1, 0));

    const double t0 = 6;
    const double tend = 16.1;
    const double dt = 0.1;
    ssc::solver::Scheduler scheduler(t0, tend, dt);

    const double discrete_system_dt = 1;
    DiscreteSystem discrete_system(t0, discrete_system_dt);
    discrete_system.schedule_update(7, scheduler);

    ssc::solver::quicksolve<EulerStepper>(system, scheduler, observer);

    ASSERT_EQ(std::vector<double>({ 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }),
              discrete_system.calltimes);
    ASSERT_EQ(13 + discrete_system.calltimes.size(), discrete_system.ticks.back());
}

TEST_F(DiscreteSystemsTests, quarter_second_steps)
{
    ssc::solver::VectorObserver observer;
    ContinuousSystem continuous_system(std::vector<double>(1, 0));

    const double t0 = 6;
    const double tend = 10;
    const double dt = 0.2;
    ssc::solver::Scheduler scheduler(t0, tend, dt);

    DiscreteSystem discrete_system(t0, 0.3);
    discrete_system.schedule_update(7, scheduler);

    ssc::solver::quicksolve<EulerStepper>(continuous_system, scheduler, observer);
    const auto observations = observer.get();

    // Check discrete system calltimes
    const std::vector<double> expected_discrete_system_calltimes
        = { 7, 7.3, 7.6, 7.9, 8.2, 8.5, 8.8, 9.1, 9.6, 9.9 };
    ASSERT_EQ(expected_discrete_system_calltimes.size(), discrete_system.calltimes.size());
    for (size_t i = 0; i < expected_discrete_system_calltimes.size(); ++i)
    {
        ASSERT_DOUBLE_EQ(expected_discrete_system_calltimes.at(i), discrete_system.calltimes.at(i));
    }
    // Check discrete system values
    ASSERT_EQ(13 + discrete_system.calltimes.size(), discrete_system.ticks.back());

    // Check continuous system calltimes
    const std::vector<double> expected_observation_instants
        = { 6,   6.2, 6.4, 6.6, 6.8, 7, 7.2, 7.3, 7.4, 7.6, 7.8, 7.9, 8,
            8.2, 8.4, 8.5, 8.6, 8.8, 9, 9.1, 9.2, 9.4, 9.6, 9.8, 9.9, 10 };
    ASSERT_EQ(expected_observation_instants.size(), observations.size());
    for (size_t i = 0; i < observations.size(); ++i)
    {
        ASSERT_DOUBLE_EQ(expected_observation_instants.at(i), observations.at(i).first);
    }
    // Check continuous system values
    for (const auto &observation : observations)
    {
        ASSERT_DOUBLE_EQ(observation.first - t0, observation.second);
    }
}

TEST_F(DiscreteSystemsTests, quarter_second_steps_with_shifted_start)
{
    ssc::solver::VectorObserver observer;
    ContinuousSystem continuous_system(std::vector<double>(1, 0));

    const double t0 = 6;
    const double tend = 10;
    const double dt = 0.2;
    ssc::solver::Scheduler scheduler(t0, tend, dt);

    DiscreteSystem discrete_system(7.325, 0.3);
    discrete_system.schedule_update(7.325, scheduler);

    ssc::solver::quicksolve<EulerStepper>(continuous_system, scheduler, observer);
    const auto observations = observer.get();

    // Check discrete system calltimes
    const std::vector<double> expected_discrete_system_calltimes
        = { 7.325, 7.625, 7.925, 8.225, 8.525, 8.825, 9.125, 9.425, 9.725 };
    ASSERT_EQ(expected_discrete_system_calltimes.size(), discrete_system.calltimes.size());
    for (size_t i = 0; i < expected_discrete_system_calltimes.size(); ++i)
    {
        ASSERT_DOUBLE_EQ(expected_discrete_system_calltimes.at(i), discrete_system.calltimes.at(i));
    }
    // Check discrete system values
    ASSERT_EQ(13 + discrete_system.calltimes.size(), discrete_system.ticks.back());

    // Check continuous system calltimes
    const std::vector<double> expected_observation_instants
        = { 6,     6.2, 6.4,   6.6, 6.8, 7,     7.2, 7.325, 7.4, 7.6, 7.625, 7.8, 7.925, 8,   8.2,
            8.225, 8.4, 8.525, 8.6, 8.8, 8.825, 9,   9.125, 9.2, 9.4, 9.425, 9.6, 9.725, 9.8, 10 };
    ASSERT_EQ(expected_observation_instants.size(), observations.size());
    for (size_t i = 0; i < observations.size(); ++i)
    {
        ASSERT_DOUBLE_EQ(expected_observation_instants.at(i), observations.at(i).first);
    }
    // Check continuous system values
    for (const auto &observation : observations)
    {
        ASSERT_DOUBLE_EQ(observation.first - t0, observation.second);
    }
}

TEST_F(DiscreteSystemsTests, quarter_second_steps_with_shifted_start_and_discrete_system_initialized_at_t0)
{
    ssc::solver::VectorObserver observer;
    ContinuousSystem continuous_system(std::vector<double>(1, 0));

    const double t0 = 6;
    const double tend = 10;
    const double dt = 0.2;
    ssc::solver::Scheduler scheduler(t0, tend, dt);

    DiscreteSystem discrete_system(t0, 0.3);
    discrete_system.schedule_update(7.325, scheduler);

    ssc::solver::quicksolve<EulerStepper>(continuous_system, scheduler, observer);
    const auto observations = observer.get();

    // Check discrete system calltimes
    const std::vector<double> expected_discrete_system_calltimes
        = { 7.325, 7.625, 7.925, 8.225, 8.525, 8.825, 9.125, 9.425, 9.725 };
    ASSERT_EQ(expected_discrete_system_calltimes.size(), discrete_system.calltimes.size());
    for (size_t i = 0; i < expected_discrete_system_calltimes.size(); ++i)
    {
        ASSERT_DOUBLE_EQ(expected_discrete_system_calltimes.at(i), discrete_system.calltimes.at(i));
    }
    // Check discrete system values
    ASSERT_EQ(13 + discrete_system.calltimes.size(), discrete_system.ticks.back());

    // Check continuous system calltimes
    const std::vector<double> expected_observation_instants
        = { 6,     6.2, 6.4,   6.6, 6.8, 7,     7.2, 7.325, 7.4, 7.6, 7.625, 7.8, 7.925, 8,   8.2,
            8.225, 8.4, 8.525, 8.6, 8.8, 8.825, 9,   9.125, 9.2, 9.4, 9.425, 9.6, 9.725, 9.8, 10 };
    ASSERT_EQ(expected_observation_instants.size(), observations.size());
    for (size_t i = 0; i < observations.size(); ++i)
    {
        ASSERT_DOUBLE_EQ(expected_observation_instants.at(i), observations.at(i).first);
    }
    // Check continuous system values
    for (const auto &observation : observations)
    {
        ASSERT_DOUBLE_EQ(observation.first - t0, observation.second);
    }
}

TEST_F(DiscreteSystemsTests, quarter_second_steps_with_rk4)
{
    ssc::solver::VectorObserver observer;
    ContinuousSystem continuous_system(std::vector<double>(1, 0));

    const double t0 = 6;
    const double tend = 10;
    const double dt = 0.2;
    ssc::solver::Scheduler scheduler(t0, tend, dt);

    DiscreteSystem discrete_system(t0, 0.3);
    discrete_system.schedule_update(7.325, scheduler);

    ssc::solver::quicksolve<RungeKuttaStepper>(continuous_system, scheduler, observer);
    const auto observations = observer.get();

    // Check discrete system calltimes
    const std::vector<double> expected_discrete_system_calltimes
        = { 7.325, 7.625, 7.925, 8.225, 8.525, 8.825, 9.125, 9.425, 9.725 };
    ASSERT_EQ(expected_discrete_system_calltimes.size(), discrete_system.calltimes.size());
    for (size_t i = 0; i < expected_discrete_system_calltimes.size(); ++i)
    {
        ASSERT_DOUBLE_EQ(expected_discrete_system_calltimes.at(i), discrete_system.calltimes.at(i));
    }
    // Check discrete system values
    ASSERT_EQ(13 + discrete_system.calltimes.size(), discrete_system.ticks.back());

    // Check continuous system calltimes
    const std::vector<double> expected_observation_instants
        = { 6,     6.2, 6.4,   6.6, 6.8, 7,     7.2, 7.325, 7.4, 7.6, 7.625, 7.8, 7.925, 8,   8.2,
            8.225, 8.4, 8.525, 8.6, 8.8, 8.825, 9,   9.125, 9.2, 9.4, 9.425, 9.6, 9.725, 9.8, 10 };
    ASSERT_EQ(expected_observation_instants.size(), observations.size());
    for (size_t i = 0; i < observations.size(); ++i)
    {
        ASSERT_DOUBLE_EQ(expected_observation_instants.at(i), observations.at(i).first);
    }
    // Check continuous system values
    for (const auto &observation : observations)
    {
        ASSERT_DOUBLE_EQ(observation.first - t0, observation.second);
    }
}