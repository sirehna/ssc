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
        y1(y.back())
{
}


void LinearInterpolation::update_coefficients_if_necessary(const double& val)
{
    update_index(val);
    x0 = xmin + idx*delta;
    x1 = x0 + delta;
    y0 = y.at(idx);
    y1 = y.at(idx+1);
}

double LinearInterpolation::get_f() const
{
    return y0+(val_sat-x0)*(y1-y0)/delta;
}

double LinearInterpolation::get_df(const size_t derivative_order) const
{
    if (derivative_order==0) return get_f();
    if (derivative_order==1) return (y1-y0)/delta;
                             return 0;
}

