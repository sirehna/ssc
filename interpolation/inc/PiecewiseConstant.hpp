/*
 * PiecewiseConstant.hpp
 *
 * \date 18 févr. 2013, 13:07:18
 *  \author cec
 */

#ifndef PIECEWISECONSTANT_HPP_
#define PIECEWISECONSTANT_HPP_

#include <vector>
#include "Interpolator.hpp"
#include "Exception.hpp"

class PiecewiseConstantException : public Exception
{
    public:
        PiecewiseConstantException(const char* s) :
                Exception(s)
        {
        }
};


/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/PiecewiseConstantTest.cpp PiecewiseConstantTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/PiecewiseConstantTest.cpp PiecewiseConstantTest expected output
 */

class PiecewiseConstant : public Interpolator
{
    public:
        PiecewiseConstant(const double& xmin_, const double& xmax_, const std::vector<double>& y_);
        double f() const;
        double df() const;
        double d2f() const;
        void set_computed_value(const double& x0);

        private:
            PiecewiseConstant();
            double xmin;
            double xmax;
            std::vector<double> y;
            size_t n;
            double delta;
            size_t idx;
};

#endif /* PIECEWISECONSTANT_HPP_ */
