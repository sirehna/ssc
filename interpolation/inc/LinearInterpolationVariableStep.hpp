/*
 * LinearInterpolationVariableStep.hpp
 *
 * \date 10 avr. 2013, 12:54:12
 *  \author cec
 */

#ifndef LINEARINTERPOLATIONVARIABLESTEP_HPP_
#define LINEARINTERPOLATIONVARIABLESTEP_HPP_

#include <vector>
#include "Exception.hpp"

class LinearInterpolationVariableStepException : public Exception
{
    public:
        LinearInterpolationVariableStepException(const char* s) :
                Exception(s)
        {
        }
};

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet interpolation/unit_tests/src/LinearInterpolationVariableStepTest.cpp LinearInterpolationVariableStepTest example
 *  \section ex2 Expected output
 *  \snippet interpolation/unit_tests/src/LinearInterpolationVariableStepTest.cpp LinearInterpolationVariableStepTest expected output
 */
class LinearInterpolationVariableStep
{
    public:
        LinearInterpolationVariableStep(const std::vector<double>& x, const std::vector<double>& y);
        double f() const;
        double df() const;
        double d2f() const;
        void set_computed_value(const double& x0);

    private:
        LinearInterpolationVariableStep();
        size_t n;
        std::vector<double> x_;
        std::vector<double> y_;
        double val;
        double der;
};

#endif /* LINEARINTERPOLATIONVARIABLESTEP_HPP_ */
