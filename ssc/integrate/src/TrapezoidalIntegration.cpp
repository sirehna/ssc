/*
 * TrapezoidalIntegration.cpp
 *
 * \date 23 avr. 2013, 14:47:22
 *  \author cec
 */

#include "TrapezoidalIntegration.hpp"
#include <cmath>

class TrapezoidalIntegration::Impl
{
    public:
        Impl()
        {

        }

        double integrate(const Function& f, const double a, const double b, const double eps) const
        {
            return integrate_n_steps(f, a, b, floor(1./fabs(eps)));
        }

        double integrate_n_steps(const Function& f, const double a, const double b, const size_t n) const
        {
            const double h = (b - a) / n;
            double S = (f(a) + f(b))/2.;
            for (size_t i  = 1 ; i < n ; ++i)
            {
                S += f(a + i * h);
            }
            return S* h;
        }

};



TrapezoidalIntegration::TrapezoidalIntegration(const Function& f) : Integrator(f), pimpl(new Impl())
{

}


double TrapezoidalIntegration::integrate(double a, double b, double eps) const
{
    return pimpl->integrate(f,a,b,eps);
}

double TrapezoidalIntegration::integrate_n_steps(double a, double b, size_t n) const
{
    return pimpl->integrate(f,a,b,n);
}
