/*
 * Interpolator.cpp
 *
 * \date 12 juin 2013, 15:26:56
 *  \author cec
 */

#include "Interpolator.hpp"

#include "InterpolatorException.hpp"

Interpolator::Interpolator() :
xmin(0), xmax(0), y(std::vector<double>()), n(0)
{

}


Interpolator::Interpolator(const double& xmin_,
        const double& xmax_,
        const std::vector<double>& y_) : xmin(xmin_), xmax(xmax_), y(y_), n(y.size())
{
    if (n < 2)
    {
        THROW(__PRETTY_FUNCTION__, InterpolatorException, "y must have at least two elements.");
    }
}
