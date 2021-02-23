/*
 * ODEMocks.hpp
 *
 * \date 19 mars 2014
 *      Author: cec
 */

#ifndef ODEMOCKS_HPP_
#define ODEMOCKS_HPP_


#include "gmock/gmock.h"

#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
#include <functional>
#include <vector>

#include "ssc/solver/EventHandler.hpp"
#include "ssc/solver/Scheduler.hpp"
#include "ssc/solver/System.hpp"
#include "ssc/solver/Observers.hpp"

class SystemWithMock;

class ODEMocks
{
    public:
        ODEMocks(){}
        MOCK_METHOD0(advance_to_next_time_event, void());
        MOCK_METHOD3(model_function, void(const std::vector<double>&, std::vector<double>&, double ));
        MOCK_METHOD2(observe, void(const ssc::solver::System&, const double));
        MOCK_METHOD4(do_step, void(ssc::solver::System& sys, std::vector<double>& , double , double ));
        MOCK_METHOD4(try_step, boost::numeric::odeint::controlled_step_result(ssc::solver::System& sys, std::vector<double>& , double , double ));
        MOCK_CONST_METHOD0(has_more_time_events, bool());
        MOCK_CONST_METHOD0(get_time, double());
        MOCK_CONST_METHOD0(get_step, double());
        MOCK_CONST_METHOD0(detected_state_events, bool());
        MOCK_CONST_METHOD1(add_time_event, void(const double));
        MOCK_CONST_METHOD0(locate_event, void());
        MOCK_CONST_METHOD0(run_event_actions, void());
};

class SystemWithMock : public ssc::solver::System
{
    public:
        SystemWithMock(ODEMocks& mock_) : mock(mock_){}
        void operator()(const std::vector<double>& x, std::vector<double>& dx_dt, double t)
        {
            mock.model_function(x, dx_dt, t);
        }

    protected:
        ODEMocks& mock;

    private:
        SystemWithMock();


};

class ObserverWithMock : public ssc::solver::Observer
{
    public:
        ObserverWithMock(ODEMocks& mock_) : mock(mock_){}
        void observe(const ssc::solver::System& s, const double d)
        {
            mock.observe(s,d);
        }

    private:
        ObserverWithMock();
        ODEMocks& mock;
};

class SchedulerWithMock : public ssc::solver::Scheduler<SystemWithMock>
{
    public:
        SchedulerWithMock(ODEMocks& mock_) : ssc::solver::Scheduler<SystemWithMock>(0,0,0), mock(mock_), first_run(new bool(true)){}
        bool has_more_time_events() const
        {
            mock.has_more_time_events();
            const bool b = *first_run;
            *first_run = false;
            return b;
        }

        void add_time_event(const double t)
        {
            mock.add_time_event(t);
        }

        ~SchedulerWithMock() noexcept
        {
            delete first_run;
        }

        SchedulerWithMock& operator=(const SchedulerWithMock& rhs)
        {
            if (this != &rhs)
            {
                *first_run = *(rhs.first_run);
            }
            return *this;
        }
        std::vector<SchedulerWithMock::Callback> get_discrete_state_updaters_to_run()
        {
            return std::vector<Callback>();
        }

        SchedulerWithMock(const SchedulerWithMock& rhs) : ssc::solver::Scheduler<SystemWithMock>(0,0,0), mock(rhs.mock), first_run(new bool(*(rhs.first_run)))
        {

        }

        double get_time() const
        {
            return mock.get_time();
        }

        double get_step() const
        {
            return mock.get_step();
        }

        void advance_to_next_time_event()
        {
            mock.advance_to_next_time_event();
        }

    private:
        SchedulerWithMock();
        ODEMocks& mock;
        bool* first_run;
};

class EventHandlerWithMock : public ssc::solver::EventHandler
{
    public:
        EventHandlerWithMock(ODEMocks& mock_) : mock(mock_){}

        bool detected_state_events() const
        {
            return mock.detected_state_events();
        }

        void locate_event()
        {
            mock.locate_event();
        }

        void run_event_actions()
        {
            mock.run_event_actions();
        }

    private:
        EventHandlerWithMock();
        ODEMocks& mock;
};

class ExplicitStepperWithMock
{
    public:
        ExplicitStepperWithMock(ODEMocks& mock_) : mock(mock_){}
        void do_step(SystemWithMock& sys, std::vector<double>& x, double t, double dt)
        {
            mock.do_step(sys,x,t,dt);
        }

    private:
        ExplicitStepperWithMock();
        ODEMocks& mock;
};

class ControlledStepperWithMock
{
    public:
        ControlledStepperWithMock(ODEMocks& mock_) : mock(mock_){}

        boost::numeric::odeint::controlled_step_result try_step(SystemWithMock& sys, std::vector<double>& x, double t, double dt)
        {
            return mock.try_step(sys,x,t,dt);
        }


    private:
        ControlledStepperWithMock();
        ODEMocks& mock;
};


#endif /* ODEMOCKS_HPP_ */
