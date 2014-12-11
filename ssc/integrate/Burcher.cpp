/*
 * Burcher.cpp
 *
 *  Created on: Dec 11, 2014
 *      Author: cady
 */

#include <cmath>

#include <ssc/integrate/Burcher.hpp>

ssc::integrate::Burcher::Burcher()
{

}

ssc::integrate::Burcher::Burcher(const Function& f) : Integrator(f)
{
}

double ssc::integrate::Burcher::integrate_n_steps(const Function& f_, double a, double b, size_t n)
{
    f = f_;
    return a+(double)n*b;
}

double ssc::integrate::Burcher::integrate_impl(const Function& f_, double a, double b, double eps)
{
    return integrate_n_steps(f_,a,b,(size_t)std::floor(1./eps));
}

