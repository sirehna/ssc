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

template <class T> class PiecewiseConstantVariableStep
{
    public:
        PiecewiseConstantVariableStep(const std::vector<double>& x, const typename std::vector<T>& y) : n(x.size()),x_(x),y_(y),val(T())
        {
            if (y.size() != n)
            {
                std::stringstream ss;
                ss << "x has size " << n
                   << ", but y has size " << y.size() << ": the two should be equal";
                THROW("PiecewiseConstantVariableStep::PiecewiseConstantVariableStep(const std::vector<double>&, const std::vector<double>&)", PiecewiseConstantVariableStepException, ss.str());
            }
            if (n < 2)
            {
                std::stringstream ss;
                ss << "x has size " << x.size() << " but size should be at least 2";
                THROW("PiecewiseConstantVariableStep::PiecewiseConstantVariableStep(const std::vector<double>&, const std::vector<double>&)", PiecewiseConstantVariableStepException, ss.str());
            }
            for (size_t i = 1 ; i < n ; ++i)
            {
                if (x.at(i)<=x.at(i-1))
                {
                    std::stringstream ss;
                    ss << "x should be in strictly increasing order: x[" << i-1 << "] = " << x.at(i-1)
                       << ", but x" << "[" << i << "] = " << x.at(i);
                    THROW("PiecewiseConstantVariableStep::PiecewiseConstantVariableStep(const std::vector<double>&, const std::vector<double>&)", PiecewiseConstantVariableStepException, ss.str());
                }
            }
        }

        T f() const
        {
            return val;
        }

        void set_computed_value(const double& x0)
        {
            if ((x0 < x_.front()) || (x0 > x_.back()))
            {
                std::stringstream ss;
                ss << "x0 should be within [" << x_.front() << "," << x_.back() << "] but received x0 = " << x0;
                THROW("PiecewiseConstantVariableStep::set_computed_value(const double&)", PiecewiseConstantVariableStepException, ss.str());
            }
            bool set = false;
            for (size_t i = 1 ; i < n ; ++i)
            {
                if (x0 < x_.at(i))
                {
                    val = y_.at(i-1);
                    set = true;
                    break;
                }
            }
            if (not(set))
            {
                val = y_.at(n-1);
            }
        }

    private:
        PiecewiseConstantVariableStep();
        size_t n;
        std::vector<double> x_;
        std::vector<T> y_;
        T val;
};

#endif /* PIECEWISECONSTANTVARIABLESTEP_HPP_ */
