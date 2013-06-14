/*
 * Interpolator.cpp
 *
 * \date 12 juin 2013, 15:26:56
 *  \author cec
 */

#include "Interpolator.hpp"
#include "InterpolatorException.hpp"
#include <cmath>

#define min(a,b) a>b?b:a

Interpolator::Interpolator() :
xmin(0), xmax(0), y(std::vector<double>()), n(0), delta(0), idx(0)
{

}


Interpolator::Interpolator(const double& xmin_,
        const double& xmax_,
        const std::vector<double>& y_) : xmin(xmin_), xmax(xmax_), y(y_), n(y.size()), delta(0), idx(0)
{
    if (n < 2)
    {
        THROW(__PRETTY_FUNCTION__, InterpolatorException, "y must have at least two elements.");
    }
    if (xmin>xmax)
    {
        THROW(__PRETTY_FUNCTION__, InterpolatorException, "xmin>xmax");
    }
    delta = (xmax-xmin)/double(n-1);
}

void Interpolator::update_index(const double x0)
{
    idx = floor((x0-xmin)/(xmax-xmin)*(n-1));
    idx = min(idx,n-2);
}

double Interpolator::f(const double x)
{
    set_computed_value(x);
    return get_f();
}

double Interpolator::df(const double x)
{
    set_computed_value(x);
    return get_df(1);
}

double Interpolator::d2f(const double x)
{
    set_computed_value(x);
    return get_df(2);
}

