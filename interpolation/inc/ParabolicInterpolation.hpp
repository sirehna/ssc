/*
 * ParabolicInterpolation.hpp
 *
 * \date 19 févr. 2013, 09:56:40
 *  \author cec
 */

#ifndef PARABOLICINTERPOLATION_HPP_
#define PARABOLICINTERPOLATION_HPP_

#include <vector>
#include "Exception.hpp"
#include "ParabolicCoefficients.hpp"

class ParabolicInterpolationException : public Exception
{
    public:
        ParabolicInterpolationException(const char* s) :
                Exception(s)
        {
        }
};


/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/ParabolicInterpolationTest.cpp ParabolicInterpolationTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/ParabolicInterpolationTest.cpp ParabolicInterpolationTest expected output
 */



class ParabolicInterpolation
{
    public:
        ParabolicInterpolation(const double& xmin, const double& xmax, const std::vector<ParabolicCoefficients>& coeffs);
        double f() const;
        double df() const;
        double d2f() const;
        void set_computed_value(const double& x0);

    private:
        ParabolicInterpolation();
        double xmin;
        double xmax;
        std::vector<ParabolicCoefficients> coeffs_;
        size_t n;
        double delta;
        double val_sat;
        double a;
        double b;
        double c;
};

#endif /* PARABOLICINTERPOLATION_HPP_ */
