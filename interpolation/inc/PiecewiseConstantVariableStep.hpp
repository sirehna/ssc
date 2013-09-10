/*
 * PiecewiseConstantVariableStep.hpp
 *
 * \date 11 avr. 2013, 08:44:51
 *  \author cec
 */

#ifndef PIECEWISECONSTANTVARIABLESTEP_HPP_
#define PIECEWISECONSTANTVARIABLESTEP_HPP_

#include <vector>
#include <sstream>
#include "Exception.hpp"
#include "VariableStepInterpolation.hpp"

class PiecewiseConstantVariableStepException : public Exception
{
    public:
        PiecewiseConstantVariableStepException(const char* s) :
                Exception(s)
        {
        }
};


/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet interpolation/unit_tests/src/PiecewiseConstantVariableStepTest.cpp PiecewiseConstantVariableStepTest example
 *  \section ex2 Expected output
 *  \snippet interpolation/unit_tests/src/PiecewiseConstantVariableStepTest.cpp PiecewiseConstantVariableStepTest expected output
 */

template <class T> class PiecewiseConstantVariableStep: public VariableStepInterpolation
{
    public:
        PiecewiseConstantVariableStep(const std::vector<double>& x, const typename std::vector<T>& y) :
            VariableStepInterpolation(x),
        y_(y),val(T())
        {
            const size_t n = x.size();
            if (y.size() != n)
            {
                std::stringstream ss;
                ss << "x has size " << n
                   << ", but y has size " << y.size() << ": they should be the same size";
                THROW(__PRETTY_FUNCTION__, PiecewiseConstantVariableStepException, ss.str());
            }
            if (x.size() < 2)
            {
                std::stringstream ss;
                ss << "x has size " << n << " but size should be at least 2";
                THROW(__PRETTY_FUNCTION__, PiecewiseConstantVariableStepException, ss.str());
            }
        }

        using Interpolator::f;
        T f(const double x0)
        {
            update_coefficients_if_necessary(x0);
            return y_[idx];
        }

        using Interpolator::df;
        T df(const double x0, const size_t derivative_order)
        {
            (void) x0;
            (void) derivative_order;
            return T();
        }

    private:
        PiecewiseConstantVariableStep();

        double get_f() const
        {
            return 0;
        }

        double get_df(const size_t derivative_order) const
        {
            (void) derivative_order;
            return 0;
        }

        std::vector<T> y_;
        T val;
};

#endif /* PIECEWISECONSTANTVARIABLESTEP_HPP_ */
