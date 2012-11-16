/*
 * LinearInterpolation.hpp
 *
 * \date 8 nov. 2012, 14:32:11
 *  \author cec
 */

#ifndef LINEARINTERPOLATION_HPP_
#define LINEARINTERPOLATION_HPP_
#include <vector>

#include "Exception.hpp"

class LinearInterpolationException : public Exception
{
    public:
        LinearInterpolationException(const char* s) :
                Exception(s)
        {
        }
};



/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet interpolation/unit_tests/src/LinearInterpolationTest.cpp LinearInterpolationTest example
 *  \section ex2 Expected output
 *  \snippet interpolation/unit_tests/src/LinearInterpolationTest.cpp LinearInterpolationTest expected output
 */

class LinearInterpolation
{
    public:
        LinearInterpolation(const double& xmin_, const double& xmax_, const std::vector<double>& y_);
        double f() const;
        double df() const;
        double d2f() const;
        void set_computed_value(const double& x0);

    private:
        LinearInterpolation();
        double xmin;
        double xmax;
        std::vector<double> y;
        double x0;
        double x1;
        double y0;
        double y1;
        size_t n;
        double delta;
        double val_sat;
};

#endif /* LINEARINTERPOLATION_HPP_ */
