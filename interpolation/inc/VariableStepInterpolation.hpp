/*
 * VariableStepInterpolation.hpp
 *
 * \date 10 sept. 2013, 11:55:03
 *  \author cec
 */

#ifndef VARIABLESTEPINTERPOLATION_HPP_
#define VARIABLESTEPINTERPOLATION_HPP_

#include "Interpolator.hpp"
#include <tr1/memory> // std::tr1::shared_ptr
#include <vector>

/** \author cec
 *  \ingroup interpolation
 *  \brief Responsibility
 *  \details 
 *  \section ex1 Example
 *  \snippet interpolation/unit_tests/src/VariableStepInterpolationTest.cpp VariableStepInterpolationTest example
 *  \section ex2 Expected output
 *  \snippet interpolation/unit_tests/src/VariableStepInterpolationTest.cpp VariableStepInterpolationTest expected output
 */

class IndexFinder;
class VariableStepInterpolation : public Interpolator
{
    public:
        virtual ~VariableStepInterpolation();
        VariableStepInterpolation(const std::vector<double>& x);

    protected:
        VariableStepInterpolation();
        size_t get_index(const double x0_) const;
        virtual double get_f() const = 0;
        virtual double get_df(const size_t derivative_order) const = 0;
        virtual void update_coefficients_if_necessary(const double x0);

    private:
        std::tr1::shared_ptr<IndexFinder> index;

    protected:
        int idx;
        double x0;
};

#endif /* VARIABLESTEPINTERPOLATION_HPP_ */
