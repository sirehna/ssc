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



/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet interpolation/unit_tests/src/PiecewiseConstantTest.cpp PiecewiseConstantTest example
 *  \section ex2 Expected output
 *  \snippet interpolation/unit_tests/src/PiecewiseConstantTest.cpp PiecewiseConstantTest expected output
 */

class PiecewiseConstant : public Interpolator
{
    public:
        PiecewiseConstant(const double& xmin_, const double& xmax_, const std::vector<double>& y_);
        void set_computed_value(const double& x0);

    private:
        PiecewiseConstant();
        double get_f() const;
        double get_df(const size_t derivative_order) const;
};

#endif /* PIECEWISECONSTANT_HPP_ */
