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

void PiecewiseConstant::update_coefficients_if_necessary(const double& x0)
{
    idx = max(0,min(floor((x0-xmin)/(xmax-xmin)*n),n-1));
}

double PiecewiseConstant::get_f() const
{
    return y.at(idx);
}

double PiecewiseConstant::get_df(const size_t derivative_order) const
{
    if (derivative_order==0) return get_f();
                             return 0;
}
