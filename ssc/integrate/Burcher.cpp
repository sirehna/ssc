/*
 * Burcher.cpp
 *
 *  Created on: Dec 11, 2014
 *      Author: cady
 */

#include <cmath>

#include <boost/math/special_functions/sinc.hpp>

#include <ssc/integrate/Burcher.hpp>
#include <ssc/macros/test_macros.hpp>

ssc::integrate::Burcher::Burcher() : Integrator() , tau(0)
{

}

ssc::integrate::Burcher::Burcher(const Function& f) : Integrator(f), tau(0)
{
}

ssc::integrate::Burcher::Burcher(const Function& f, const double tau_) : Integrator(f), tau(tau_)
{
}

double ssc::integrate::Burcher::compute_for(const double tau_, const double a, const double b, const double eps)
{
    tau = tau_;
    return Integrator::integrate(f, a, b, eps);
}

double ssc::integrate::Burcher::integrate(const std::vector<double>& omegas) const
{
    double res = 0;
    const size_t n = omegas.size();
    std::vector<double> f_omegas(n,0);
    f_omegas[0] = f(omegas.front());
    for (size_t i = 0 ; i < n - 1 ; ++i)
    {
        f_omegas[i+1] = f(omegas[i+1]);
        const double Omega = (omegas[i+1] + omegas[i])/2.;
        const double sinc1 = boost::math::sinc_pi(tau*Omega);
        const double sinc2 = boost::math::sinc_pi(tau*(omegas[i+1] - omegas[i])/2.);
        res += (f_omegas[i] - f_omegas[i+1])*Omega*sinc1*sinc2;
    }
    return res;
}

double ssc::integrate::Burcher::integrate_n_steps(const Function& f_, double a, double b, size_t n)
{
    f = f_;
    std::vector<double> omegas(n,0);
    for (size_t i = 0 ; i < n ; ++i)
    {
        omegas[i] = a + (b-a)*((double)i)/((double)n-1);
    }
    return integrate(omegas);
}

double ssc::integrate::Burcher::integrate_impl(const Function& f_, double a, double b, double eps)
{
    return integrate_n_steps(f_,a,b,(size_t)std::floor(1./eps));
}

