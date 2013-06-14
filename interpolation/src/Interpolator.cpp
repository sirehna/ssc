/*
 * Interpolator.cpp
 *
 * \date 12 juin 2013, 15:26:56
 *  \author cec
 */

#include "Interpolator.hpp"
#include "InterpolatorException.hpp"
#include <cmath>

#include "test_macros.hpp"


Interpolator::Interpolator() :
xmin(0), xmax(0), y(std::vector<double>()), n(0), delta(0), idx(0)
{

}


Interpolator::Interpolator(const double& xmin_,
        const double& xmax_,
        const std::vector<double>& y_) : xmin(xmin_), xmax(xmax_), y(y_), n(y.size()), delta(0), idx(0)
{
    COUT(xmin);
    COUT(xmax);
    COUT(y_.front());
    COUT(y_.back());
    COUT(n);
    std::cout << "____________________________________" << std::endl;
    if (n == 0)
    {
        THROW(__PRETTY_FUNCTION__, InterpolatorException, "y must have at least one element.");
    }
    if (xmin>xmax)
    {
        THROW(__PRETTY_FUNCTION__, InterpolatorException, "xmin>xmax");
    }
    delta = n==1 ? (xmax-xmin) : (xmax-xmin)/double(n-1);
}

void Interpolator::update_index(const double x0)
{
    idx = (n==1) ? 0 : floor((x0-xmin)/(xmax-xmin)*(n-1));
    idx = std::min(idx,n-2);
}

double Interpolator::f(const double x)
{
    update_coefficients_if_necessary(x);
    return get_f();
}

double Interpolator::df(const double x)
{
    update_coefficients_if_necessary(x);
    return get_df(1);
}

double Interpolator::d2f(const double x)
{
    update_coefficients_if_necessary(x);
    return get_df(2);
}

