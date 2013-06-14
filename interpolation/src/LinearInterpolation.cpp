/*
 * LinearInterpolation.cpp
 *
 * \date 8 nov. 2012, 14:32:11
 *  \author cec
 */

#include "LinearInterpolation.hpp"
#define min(a,b) (a)>(b)?b:a
#define max(a,b) (a)>(b)?a:b
#include <math.h>
#include "test_macros.hpp"

LinearInterpolation::LinearInterpolation(const double& xmin_,
        const double& xmax_,
        const std::vector<double>& y_) : Interpolator(xmin_,xmax_,y_)/*xmin(xmin_), xmax(xmax_), y(y_)*/,
        x0(xmin),
        x1(xmax),
        y0(y.front()),
        y1(y.back()),
n(y.size()),
delta((xmax-xmin)/double(n-1)),
val_sat(xmin)
{
    if (y.size() < 2)
    {
        THROW("LinearInterpolation::LinearInterpolation(const double&, const double&, const std::vector<double>&)", Exception, "y must have at least two elements.");
    }
}


void LinearInterpolation::set_computed_value(const double& val)
{
    val_sat = max(xmin,min(xmax,val));
    const size_t idx = max(0,min(floor((val_sat-xmin)/(xmax-xmin)*(n-1)),n-2));
    x0 = xmin + idx*delta;
    x1 = x0 + delta;
    y0 = y.at(idx);
    y1 = y.at(idx+1);
}

double LinearInterpolation::f() const
{
    return y0+(val_sat-x0)*(y1-y0)/delta;
}

double LinearInterpolation::df() const
{
    return (y1-y0)/delta;
}

double LinearInterpolation::d2f() const
{
    return 0;
}

