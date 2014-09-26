/*
 * OptimizationResult.cpp
 *
 * \date 22 févr. 2013, 15:54:39
 *  \author cec
 */

#include "OptimizationResult.hpp"


OptimizationResult::OptimizationResult() :
nb_of_iterations(0),
value_of_the_objective_function(0),
total_time_needed_for_optimization(0),
state_values(std::map<std::string,double>()),
constraint_values(std::vector<double>()),
gradient_of_the_objective_function(SparseVector()),
constraint_jacobian(SparseMatrix()),
hessian_of_the_lagrangian(SparseMatrix()),
converged(false)
{}
