/*
 * Interpolator.cpp
 *
 * \date 12 juin 2013, 15:26:56
 *  \author cec
 */

#include "Interpolator.hpp"

#include "Exception.hpp"

class InterpolatorException : public Exception
{
    public:
        InterpolatorException(const char* s) :
                Exception(s)
        {
        }
};


Interpolator::Interpolator(const double& xmin_,
        const double& xmax_,
        const std::vector<double>& y_) : xmin(xmin_), xmax(xmax_), y(y_)
{
    if (y.size() < 2)
    {
        THROW(__PRETTY_FUNCTION__, InterpolatorException, "y must have at least two elements.");
    }
}
