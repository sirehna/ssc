/*
 * Rectangle.cpp
 *
 *  Created on: Nov 28, 2014
 *      Author: cady
 */

#include "Rectangle.hpp"
#include <cmath>
#include <cstdlib>
#include "ssc/macros/test_macros.hpp"
ssc::integrate::Rectangle::Rectangle(const Function& f) : ssc::integrate::Integrator(f)
{

}

double ssc::integrate::Rectangle::integrate(double a, double b, double eps) const
{
    const double h = (b-a)*eps;
    const size_t N = (size_t)std::floor(1./eps);
    double I = 0;
    for (size_t i = 0 ; i < N ; ++i) I += f(a+(double)i*h);
    return h*I;
}
