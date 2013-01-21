#include "LinearInterpolator.hpp"
#include <cmath>

#define MIN(a,b) (a>b) ? b : a

LinearInterpolator::LinearInterpolator(const double& xmin_, const double& xmax_, const std::vector<double>& y_) : idx(0), xmin(xmin_),xmax(xmax_),y(y_), n(y.size()), delta_x((xmax-xmin)/(n-1.)), x(xmin)
{
}

void LinearInterpolator::set_x(const double& x0)
{
    idx = MIN(n-2, floor((x0-xmin)/delta_x));
    x = x0;
}

double LinearInterpolator::f() const
{
    return y.at(idx) + (x-idx*delta_x)*delta_x;
}

double LinearInterpolator::df() const
{
    return (y.at(idx+1)-y.at(idx))/delta_x;
}


