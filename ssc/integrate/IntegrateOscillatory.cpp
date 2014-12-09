/*
 * IntegrateOscillatory.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: cady
 */

#include <ssc/integrate/IntegrateOscillatory.hpp>

ssc::integrate::IntegrateOscillatory::IntegrateOscillatory() : QuadPack()
{
}
ssc::integrate::IntegrateOscillatory::IntegrateOscillatory(const Function& f_) : QuadPack(f_)
{
}

double ssc::integrate::IntegrateOscillatory::integrate_impl(const Function& f, double a, double b, double eps)
{
    return f(a+b+eps);
}

