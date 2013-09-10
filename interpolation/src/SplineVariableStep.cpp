/*
 * SplineVariableStep.cpp
 *
 * \date 9 sept. 2013, 10:47:42
 *  \author cec
 */

#include "SplineVariableStep.hpp"

SplineVariableStep::SplineVariableStep(const std::vector<double>& x, const std::vector<double>& y)
{
    (void)x;
    (void)y;
}

double SplineVariableStep::get_f() const
{
    return 1;
}

double SplineVariableStep::get_df(const size_t derivative_order) const
{
    return (double) derivative_order;
}

void SplineVariableStep::update_coefficients_if_necessary(const double x0)
{
    (void)x0;
}
