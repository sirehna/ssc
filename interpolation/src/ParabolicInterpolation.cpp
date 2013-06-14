/*
 * ParabolicInterpolation.cpp
 *
 * \date 19 févr. 2013, 09:56:40
 *  \author cec
 */

#include "ParabolicInterpolation.hpp"
#include "ParabolicInterpolationException.hpp"
#define min(a,b) (a)>(b)?b:a
#define max(a,b) (a)>(b)?a:b
#include <math.h>

ParabolicInterpolation::ParabolicInterpolation(const double& xmin_,
        const double& xmax_,
        const std::vector<ParabolicCoefficients>& coeffs) : Interpolator(xmin_,xmax_,std::vector<double>(2,0)), coeffs_(coeffs),
a(0),
b(0),
c(0),
x_xi(0)
{
    n = coeffs.size()+1;
    if (coeffs.size() < 2)
    {
        THROW(__PRETTY_FUNCTION__, ParabolicInterpolationException, "Too few elements in coeffs (requires at least 2)");
    }
    delta = (xmax-xmin)/double(n-1);
}

void ParabolicInterpolation::set_computed_value(const double& val)
{
    const double val_sat = max(xmin,min(xmax,val));
    const size_t idx = max(0,min(floor((val_sat-xmin)/(xmax-xmin)*(n-1)),n-2));
    a = coeffs_.at(idx).a;
    b = coeffs_.at(idx).b;
    c = coeffs_.at(idx).c;
    x_xi = val_sat - (xmin + delta*idx);
}

double ParabolicInterpolation::f(const double x0)
{
    set_computed_value(x0);
    return a*x_xi*x_xi+b*x_xi+c;
}

double ParabolicInterpolation::df(const double x0)
{
    set_computed_value(x0);
    return 2*a*x_xi+b;
}

double ParabolicInterpolation::d2f(const double x0)
{
    set_computed_value(x0);
    return 2*a;
}

double ParabolicInterpolation::get_f() const
{
    return a*x_xi*x_xi+b*x_xi+c;
}

double ParabolicInterpolation::get_df(const size_t derivative_order) const
{
    if (derivative_order==0) return get_f();
    if (derivative_order==1) return 2*a*x_xi+b;
    if (derivative_order==2) return 2*a;
                             return 0;
}
