/*
 * Interpolator.hpp
 *
 * \date 12 juin 2013, 15:26:55
 *  \author cec
 */

#ifndef INTERPOLATOR_HPP_
#define INTERPOLATOR_HPP_

#include <vector>

/** \author cec
 *  \ingroup MODULE_NAME
 *  \brief Generic interface to interpolation classes
 *  \details 
 *  \section ex1 Example
 *  \snippet interpolation/unit_tests/src/InterpolatorTest.cpp InterpolatorTest example
 *  \section ex2 Expected output
 *  \snippet interpolation/unit_tests/src/InterpolatorTest.cpp InterpolatorTest expected output
 */

class Interpolator
{
    public:
        Interpolator();
        virtual ~Interpolator() {}
        Interpolator(const double& xmin_, const double& xmax_, const std::vector<double>& y);
        virtual void set_computed_value(const double& x0) = 0;
        virtual double f() const = 0;
        virtual double df() const = 0;
        virtual double d2f() const = 0;



    protected:
        double xmin;
        double xmax;
        std::vector<double> y;
        size_t n;
};

#endif /* INTERPOLATOR_HPP_ */
