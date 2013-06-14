/*
 * LinearInterpolation.hpp
 *
 * \date 8 nov. 2012, 14:32:11
 *  \author cec
 */

#ifndef LINEARINTERPOLATION_HPP_
#define LINEARINTERPOLATION_HPP_
#include <vector>
#include "Interpolator.hpp"




/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet interpolation/unit_tests/src/LinearInterpolationTest.cpp LinearInterpolationTest example
 *  \section ex2 Expected output
 *  \snippet interpolation/unit_tests/src/LinearInterpolationTest.cpp LinearInterpolationTest expected output
 */

class LinearInterpolation : public Interpolator
{
    public:
        LinearInterpolation(const double& xmin_, const double& xmax_, const std::vector<double>& y_);
        void set_computed_value(const double& x0);

    private:
        LinearInterpolation();
        double get_f() const;
        double get_df(const size_t derivative_order) const;
        double x0;
        double x1;
        double y0;
        double y1;
        double val_sat;
};

#endif /* LINEARINTERPOLATION_HPP_ */
