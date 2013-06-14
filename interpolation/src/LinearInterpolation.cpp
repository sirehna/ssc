/*
 * LinearInterpolation.cpp
 *
 * \date 8 nov. 2012, 14:32:11
 *  \author cec
 */


#include "LinearInterpolation.hpp"
#include <cmath>

LinearInterpolation::LinearInterpolation(const double& xmin_,
        const double& xmax_,
        const std::vector<double>& y_) : Interpolator(xmin_,xmax_,y_),
        x0(xmin),
        x1(xmax),
        y0(y.front()),
        y1(y.back()),
val_sat(xmin)
{
}


void LinearInterpolation::set_computed_value(const double& val)
{
    val_sat = std::max(xmin,std::min(xmax,val));
    const size_t idx = std::max(0.,std::min(floor((val_sat-xmin)/(xmax-xmin)*(n-1)),(double)n-2));
    x0 = xmin + idx*delta;
    x1 = x0 + delta;
    y0 = y.at(idx);
    y1 = y.at(idx+1);
}

double LinearInterpolation::f(const double x)
{
    set_computed_value(x);
    return y0+(val_sat-x0)*(y1-y0)/delta;
}

double LinearInterpolation::df(const double x)
{
    set_computed_value(x);
    return (y1-y0)/delta;
}

double LinearInterpolation::d2f(const double x)
{
    (void)x;
    return 0;
}

