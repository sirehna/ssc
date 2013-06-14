/*
 * LinearInterpolationVariableStep.hpp
 *
 * \date 10 avr. 2013, 12:54:12
 *  \author cec
 */

#ifndef LINEARINTERPOLATIONVARIABLESTEP_HPP_
#define LINEARINTERPOLATIONVARIABLESTEP_HPP_

#include <vector>
#include <tr1/memory>
#include "Interpolator.hpp"

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet interpolation/unit_tests/src/LinearInterpolationVariableStepTest.cpp LinearInterpolationVariableStepTest example
 *  \section ex2 Expected output
 *  \snippet interpolation/unit_tests/src/LinearInterpolationVariableStepTest.cpp LinearInterpolationVariableStepTest expected output
 */
class LinearInterpolationVariableStep : public Interpolator
{
    public:
        LinearInterpolationVariableStep(const std::vector<double>& x, const std::vector<double>& y);

    private:
        LinearInterpolationVariableStep();
        void update_coefficients_if_necessary(const double& x0);
        double get_f() const;
        double get_df(const size_t derivative_order) const;
        class LinearInterpolationVariableStepImpl;
        std::tr1::shared_ptr<LinearInterpolationVariableStepImpl> pimpl;
};

#endif /* LINEARINTERPOLATIONVARIABLESTEP_HPP_ */
