/*
 * ParabolicInterpolation.cpp
 *
 * \date 19 févr. 2013, 09:56:40
 *  \author cec
 */

#include "ParabolicInterpolation.hpp"


#define min(a,b) (a)>(b)?b:a
#define max(a,b) (a)>(b)?a:b
#include <math.h>

ParabolicInterpolation::ParabolicInterpolation(const double& xmin_,
        const double& xmax_,
        const std::vector<ParabolicCoefficients>& coeffs) : xmin(xmin_), xmax(xmax_), coeffs_(coeffs),
n(coeffs.size()+1),
delta(0),
a(0),
b(0),
c(0),
x_xi(0)
{
    if (n < 3)
    {
        THROW("ParabolicInterpolation::ParabolicInterpolation(const double&, const double&, const std::vector<double>&)", ParabolicInterpolationException, "y must have at least two elements.");
    }
    if (xmin>xmax)
    {
        THROW("ParabolicInterpolation::ParabolicInterpolation(const double&, const double&, const std::vector<ParabolicCoefficients>&)", ParabolicInterpolationException, "xmin>xmax");
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

double ParabolicInterpolation::f() const
{
    return a*x_xi*x_xi+b*x_xi+c;
}

double ParabolicInterpolation::df() const
{
    return 2*a*x_xi+b;
}

double ParabolicInterpolation::d2f() const
{
    return 2*a;
}

