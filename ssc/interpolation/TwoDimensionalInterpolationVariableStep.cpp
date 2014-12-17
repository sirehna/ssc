/*
 * TwoDimensionalInterpolationVariableStep.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: cady
 */

#include "TwoDimensionalInterpolationVariableStep.hpp"

ssc::interpolation::TwoDimensionalInterpolationVariableStep::TwoDimensionalInterpolationVariableStep() : y_interpolators_for_each_x(),
        allow_queries_outside_bounds(), x()
{
}

ssc::interpolation::TwoDimensionalInterpolationVariableStep::TwoDimensionalInterpolationVariableStep(const std::vector<double>& x_, const std::vector<double>& y, const std::vector<std::vector<double> >& M, const bool allow_queries_outside_bounds_) :
        y_interpolators_for_each_x(),
        allow_queries_outside_bounds(allow_queries_outside_bounds_),
        x(x_)
{
    for (auto it = M.begin() ; it != M.end() ; ++it)
    {
        y_interpolators_for_each_x.push_back(SplineVariableStep(y, *it, allow_queries_outside_bounds));
    }
}

double ssc::interpolation::TwoDimensionalInterpolationVariableStep::f(const double x0, const double y0)
{
    std::vector<double> interpolated_values_for_x_fixed;
    for (auto it = y_interpolators_for_each_x.begin() ; it != y_interpolators_for_each_x.end() ; ++it)
    {
        interpolated_values_for_x_fixed.push_back(it->f(y0));
    }
    SplineVariableStep final_interpolation(x,interpolated_values_for_x_fixed);
    return final_interpolation.f(x0);
}
