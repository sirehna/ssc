/*
 * IpoptSolver.cpp
 *
 * \date 22 févr. 2013, 15:28:59
 *  \author cec
 */

#include "IpoptSolver.hpp"
#include "OptimizationResult.hpp"

class IpoptSolver::IpoptSolverPimpl
{
};

IpoptSolver::IpoptSolver(const OptimizationProblem& problem) : pimpl(new IpoptSolverPimpl())
{
    (void) problem;
}

OptimizationResult IpoptSolver::solve(const std::vector<double>& starting_point)
{
    OptimizationResult ret;
    ret.state_values = starting_point;
    return ret;
}
