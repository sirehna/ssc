/*
 * Filon.cpp
 *
 *  Created on: Dec 10, 2014
 *      Author: cady
 */

#include "ssc/integrate/Filon.hpp"

ssc::integrate::Filon::Filon()
{

}

ssc::integrate::Filon::Filon(const Function& f_, const double tau_) : Integrator(f_), tau(tau_)
{

}

double ssc::integrate::Filon::compute_for(const double tau_, const double a, const double b, const double eps)
{
    tau = tau_;
    return a+b+eps;
}

double ssc::integrate::Filon::integrate_impl(const Function& f_, double a, double b, double eps)
{
    f = f_;
    return compute_for(tau, a, b, eps);
}
