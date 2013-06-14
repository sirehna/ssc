/*
 * PiecewiseConstant.cpp
 *
 * \date 18 févr. 2013, 13:07:18
 *  \author cec
 */

#include "PiecewiseConstant.hpp"
#include "PiecewiseConstantException.hpp"
#include <cmath>

PiecewiseConstant::PiecewiseConstant(const double& xmin_, const double& xmax_, const std::vector<double>& y_) :
Interpolator(xmin_,xmax_,y_)
{
    if (n < 2)
    {
        THROW(__PRETTY_FUNCTION__, PiecewiseConstantException, "Needs at least two points in vector y");
    }
}

void PiecewiseConstant::update_coefficients_if_necessary(const double& x0)
{
    idx = std::max(0,std::min((int)floor((x0-xmin)/(xmax-xmin)*n),(int)n-1));
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
