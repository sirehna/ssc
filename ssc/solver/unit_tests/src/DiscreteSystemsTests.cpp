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

    void operator()(const std::vector<double> &, std::vector<double> &, double )
    {
    }
};

struct DiscreteSystem
{
    DiscreteSystem(const double dt_) : ticks({13}), dt(dt_) {}
    void operator()(ssc::solver::Scheduler<ContinuousSystem>& scheduler, ContinuousSystem& )
    {
        ssc::solver::Scheduler<ContinuousSystem>::Callback callback = std::bind(&DiscreteSystem::operator(), this, std::placeholders::_1, std::placeholders::_2);
        scheduler.schedule_discrete_state_update(scheduler.get_time() + 1, callback);
        ticks.push_back(ticks.back()+1);
    }
    std::vector<size_t> ticks;
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
    ASSERT_EQ(22, discrete_system.ticks.back());
}

