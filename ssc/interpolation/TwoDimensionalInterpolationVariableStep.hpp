/*
 * TwoDimensionalInterpolationVariableStep.hpp
 *
 *  Created on: Dec 17, 2014
 *      Author: cady
 */

#ifndef TWODIMENSIONALINTERPOLATIONVARIABLESTEP_HPP_
#define TWODIMENSIONALINTERPOLATIONVARIABLESTEP_HPP_


#include "ssc/interpolation/LinearInterpolationVariableStep.hpp"
#include <vector>
#include "ssc/macros/tr1_macros.hpp"
#include TR1INC(memory)

#include "ssc/exception_handling/Exception.hpp"

/** \brief
 *  \details
 *  \addtogroup interpolation
 *  \ingroup interpolation
 *  \section ex1 Example
 *  \snippet interpolation/unit_tests/src/TwoDimensionalInterpolationVariableStepTest.cpp TwoDimensionalInterpolationVariableStepTest example
 *  \section ex2 Expected output
 *  \snippet interpolation/unit_tests/src/TwoDimensionalInterpolationVariableStepTest.cpp TwoDimensionalInterpolationVariableStepTest expected output
 */
namespace ssc
{
    namespace interpolation
    {
        class TwoDimensionalInterpolationVariableStep
        {
            public:
                TwoDimensionalInterpolationVariableStep();
                TwoDimensionalInterpolationVariableStep(const std::vector<double>& x, const std::vector<double>& y, const std::vector<std::vector<double> >& M, const bool allow_queries_outside_bounds = false);
                double f(const double x0, const double y0);

            private:
                std::vector<LinearInterpolationVariableStep> y_interpolators_for_each_x;
                bool allow_queries_outside_bounds;
                std::vector<double> x;
        };
    }
}

#endif /* TWODIMENSIONALINTERPOLATIONVARIABLESTEP_HPP_ */
