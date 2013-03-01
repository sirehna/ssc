/*
 * OptimizationResult.hpp
 *
 * \date 22 févr. 2013, 15:54:39
 *  \author cec
 */

#ifndef OPTIMIZATIONRESULT_HPP_
#define OPTIMIZATIONRESULT_HPP_

#include "SparseVector.hpp"
#include "SparseMatrix.hpp"

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/OptimizationResultTest.cpp OptimizationResultTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/OptimizationResultTest.cpp OptimizationResultTest expected output
 */

struct OptimizationResult
{
    OptimizationResult();
    size_t nb_of_iterations;
    double value_of_the_objective_function;
    double total_time_needed_for_optimization;
    std::vector<double> state_values;
    SparseVector gradient_of_the_objective_function;
    SparseMatrix constraint_jacobian;
    SparseMatrix hessian_of_the_lagrangian;

};

#endif /* OPTIMIZATIONRESULT_HPP_ */
