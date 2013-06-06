/*
 * TrapezoidalIntegration.cpp
 *
 * \date 23 avr. 2013, 14:47:22
 *  \author cec
 */

#include "TrapezoidalIntegration.hpp"
#include <cmath>
#include "test_macros.hpp"
class TrapezoidalIntegration::Impl
{
    public:
        Impl()
        {

        }

        double integrate(const Function& f, const double& a, const double& b, const double& eps) const
        {
            const size_t nb_of_evaluations = floor(1./fabs(eps));
            const double h = (b - a) / nb_of_evaluations;
            double S = f(a) + f(b);
            for (size_t i  = 1 ; i < nb_of_evaluations ; ++i)
            {
                S += 2 * f(a + i * h);
            }
            return S * h / 2.;
        }
};



TrapezoidalIntegration::TrapezoidalIntegration(const Function& f) : Integrator(f), pimpl(new Impl())
{

}


double TrapezoidalIntegration::integrate(const double& a, const double& b, const double& eps) const
{
    return pimpl->integrate(f,a,b,eps);
}
