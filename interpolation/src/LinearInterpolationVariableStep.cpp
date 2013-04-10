/*
 * LinearInterpolationVariableStep.cpp
 *
 * \date 10 avr. 2013, 12:54:12
 *  \author cec
 */

#include "LinearInterpolationVariableStep.hpp"
#include <sstream>

LinearInterpolationVariableStep::LinearInterpolationVariableStep(const std::vector<double>& x, const std::vector<double>& y) : n(x.size()), x_(x), y_(y), val(0), der(0)
{
    if (y.size() != n)
    {
        std::stringstream ss;
        ss << "x has size " << n
           << ", but y has size " << y.size() << ": the two should be equal";
        THROW("LinearInterpolationVariableStep::LinearInterpolationVariableStep(const std::vector<double>&, const std::vector<double>&)", LinearInterpolationVariableStepException, ss.str());
    }
    if (n < 2)
    {
        std::stringstream ss;
        ss << "x has size " << x.size() << " but size should be at least 2";
        THROW("LinearInterpolationVariableStep::LinearInterpolationVariableStep(const std::vector<double>&, const std::vector<double>&)", LinearInterpolationVariableStepException, ss.str());
    }
    for (size_t i = 1 ; i < n ; ++i)
    {
        if (x.at(i)<=x.at(i-1))
        {
            std::stringstream ss;
            ss << "x should be in strictly increasing order: x[" << i-1 << "] = " << x.at(i-1)
               << ", but x" << "[" << i << "] = " << x.at(i);
            THROW("LinearInterpolationVariableStep::LinearInterpolationVariableStep(const std::vector<double>&, const std::vector<double>&)", LinearInterpolationVariableStepException, ss.str());
        }
    }
}

double LinearInterpolationVariableStep::f() const
{
    return val;
}

double LinearInterpolationVariableStep::df() const
{
    return der;
}

double LinearInterpolationVariableStep::d2f() const
{
    return 0;
}

void LinearInterpolationVariableStep::set_computed_value(const double& x0)
{
    if ((x0 < x_.front()) || (x0 > x_.back()))
    {
        std::stringstream ss;
        ss << "x0 should be within [" << x_.front() << "," << x_.back() << "] but received x0 = " << x0;
        THROW("LinearInterpolationVariableStep::set_computed_value(const double&)", LinearInterpolationVariableStepException, ss.str());
    }
    bool set = false;
    for (size_t i = 1 ; i < n ; ++i)
    {
        if (x0 < x_.at(i))
        {
            der = (y_.at(i) - y_.at(i-1))/(x_.at(i) - x_.at(i-1));
            val = der*(x0-x_.at(i-1)) + y_.at(i-1);
            set = true;
            break;
        }
    }
    if (not(set))
    {
        der = (y_.at(n-1) - y_.at(n-2))/(x_.at(n-1) - x_.at(n-2));
        val = y_.at(n-1);
    }
}
