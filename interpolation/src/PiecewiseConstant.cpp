/*
 * PiecewiseConstant.cpp
 *
 * \date 18 févr. 2013, 13:07:18
 *  \author cec
 */

#include "PiecewiseConstant.hpp"
#include <cmath>

#define min(a,b) (a)>(b)?b:a
#define max(a,b) (a)>(b)?a:b

PiecewiseConstant::PiecewiseConstant(const double& xmin_, const double& xmax_, const std::vector<double>& y_) :
Interpolator(xmin_,xmax_,y_)
{
}

double PiecewiseConstant::f() const
{
    return y.at(idx);
}

double PiecewiseConstant::df() const
{
    return 0;
}

double PiecewiseConstant::d2f() const
{
    return 0;
}

void PiecewiseConstant::set_computed_value(const double& x0)
{
    idx = max(0,min(floor((x0-xmin)/(xmax-xmin)*n),n-1));
}
