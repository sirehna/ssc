/*
 * ODEintTests.cpp
 *
 * \date February 23 2021
 *      Author: CEC
 */

#include "DiscreteSystemsTests.hpp"

#include <functional> // Otherwise CLang issues an error (bind.hpp:36:14: error: ‘std::bind’ has not been declared)
#include "ssc/solver/Observers.hpp"
#include "ssc/solver/Scheduler.hpp"
#include "ssc/solver/solve.hpp"
#include "test_systems.hpp"

#include <boost/numeric/odeint/stepper/euler.hpp>

#include <sstream>

DiscreteSystemsTests::DiscreteSystemsTests() : a(ssc::random_data_generator::DataGenerator(36))
{
}

DiscreteSystemsTests::~DiscreteSystemsTests()
{
}

void DiscreteSystemsTests::SetUp()
{
}

void DiscreteSystemsTests::TearDown()
{
}

typedef boost::numeric::odeint::euler<StateType> EulerStepper;

struct ContinuousSystem : public ssc::solver::System
{
    ContinuousSystem(const std::vector<double>& x0)
    {
        state = x0;
    }

    void operator()(const std::vector<double> &, std::vector<double> &dx_dt, double )
    {
        dx_dt[0] = 1;
    }
};

struct DiscreteSystem
{
    DiscreteSystem(const double dt_) : ticks({13}), calltimes(), dt(dt_) {}
    void operator()(ssc::solver::Scheduler<ContinuousSystem>& scheduler, ContinuousSystem& )
    {
        ssc::solver::Scheduler<ContinuousSystem>::Callback callback = std::bind(&DiscreteSystem::operator(), this, std::placeholders::_1, std::placeholders::_2);
        scheduler.schedule_discrete_state_update(scheduler.get_time() + dt, callback);
        ticks.push_back(ticks.back()+1);
        calltimes.push_back(scheduler.get_time());
    }
    std::vector<size_t> ticks;
    std::vector<double> calltimes;
    const double dt;
};

TEST_F(DiscreteSystemsTests, one_second_steps)
{
    ssc::solver::VectorObserver observer;
    ssc::solver::Scheduler<ContinuousSystem> scheduler(6, 16, 0.1);
    ContinuousSystem system(std::vector<double>(1,0));
    DiscreteSystem discrete_system(1);
    ssc::solver::Scheduler<ContinuousSystem>::Callback callback = std::bind(&DiscreteSystem::operator(), &discrete_system, std::placeholders::_1, std::placeholders::_2);
    scheduler.schedule_discrete_state_update(7, callback);
    ssc::solver::quicksolve<EulerStepper>(system, scheduler, observer);
    ASSERT_EQ(23, discrete_system.ticks.back());
}

TEST_F(DiscreteSystemsTests, quarter_second_steps)
{
    ssc::solver::VectorObserver observer;
    const double t0 = 6;
    const double tend = 10;
    const double dt = 0.2;
    ssc::solver::Scheduler<ContinuousSystem> scheduler(t0, tend, dt);
    ContinuousSystem continuous_system(std::vector<double>(1,0));
    DiscreteSystem discrete_system(0.3);
    ssc::solver::Scheduler<ContinuousSystem>::Callback callback = std::bind(&DiscreteSystem::operator(), &discrete_system, std::placeholders::_1, std::placeholders::_2);
    scheduler.schedule_discrete_state_update(7.325, callback);
    ssc::solver::quicksolve<EulerStepper>(continuous_system, scheduler, observer);
    const auto observations = observer.get();
    ASSERT_EQ(22, discrete_system.ticks.back());
    // Check instants
    const std::vector<double> expected_observation_instants = {6, 6.2, 6.4, 6.6, 6.8, 7, 7.2, 7.325, 7.4, 7.6, 7.625, 7.8, 7.925, 8, 8.2, 8.225, 8.4, 8.525, 8.6, 8.8, 8.825, 9, 9.125, 9.2, 9.4, 9.425, 9.6, 9.725, 9.8, 10};
    ASSERT_EQ(expected_observation_instants.size(), observations.size());
    for (size_t i = 0 ; i < 30 ; ++i)
    {
        ASSERT_DOUBLE_EQ(expected_observation_instants.at(i), observations.at(i).first);
    }
    // Check values
    for (const auto& observation:observations)
    {
        ASSERT_DOUBLE_EQ(observation.first - t0, observation.second);
    }
}
