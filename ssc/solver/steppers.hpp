/*
 * steppers.hpp
 *
 * \date Jun 30, 2014
 * \author cec
 */

#ifndef STEPPERS_HPP_
#define STEPPERS_HPP_

#include <boost/numeric/odeint/stepper/euler.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_cash_karp54.hpp>

#include "ssc/solver/System.hpp"

namespace ssc
{
    namespace solver
    {
        class Stepper
        {
            public:
                virtual ~Stepper() = default;
                virtual void do_step(System& system, std::vector<double>& state, const double t, const double dt) = 0;
        };

        class SystemWrapper
        {
            public:
                SystemWrapper(System& s) : system(&s)
                {}
                void operator()(const std::vector<double>& x, std::vector<double>& dx_dt, const double t)
                {
                    system->operator()(x, dx_dt, t);
                }
                ~SystemWrapper() {}
                SystemWrapper(const SystemWrapper& rhs) : system(rhs.system) {}
                SystemWrapper& operator=(const SystemWrapper& rhs) { system = rhs.system; return *this;}
            private:
                SystemWrapper();
                System* system;
        };

        class EulerStepper : public Stepper
        {
            public:
                EulerStepper() : stepper() {}
                void do_step(System& system, std::vector<double>& state, const double t, const double dt)
                {
                    stepper.do_step(SystemWrapper(system), state, t, dt);
                }

            private:
                ::boost::numeric::odeint::euler<std::vector<double> > stepper;
        };

        class RK4Stepper : public Stepper
        {
            public:
                RK4Stepper() : stepper() {}
                void do_step(System& system, std::vector<double>& state, const double t, const double dt)
                {
                    stepper.do_step(SystemWrapper(system), state, t, dt);
                }

            private:
                ::boost::numeric::odeint::runge_kutta4<std::vector<double> > stepper;
        };

        class RKCK : public Stepper
        {
            public:
                RKCK() : stepper() {}
                void do_step(System& system, std::vector<double>& state, const double t, const double dt)
                {
                    stepper.do_step(SystemWrapper(system), state, t, dt);
                }

            private:
                ::boost::numeric::odeint::runge_kutta_cash_karp54<std::vector<double> > stepper;
        };
    }
}

#endif /* STEPPERS_HPP_ */
