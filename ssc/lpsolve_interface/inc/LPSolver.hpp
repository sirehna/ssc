/*
 * LPSolver.hpp
 *
 * \date 20 nov. 2013, 14:01:21
 *  \author cec
 */

#ifndef LPSOLVER_HPP_
#define LPSOLVER_HPP_

#include <memory>
#include "OptimizationResult.hpp"

class OptimizationProblem;

/** \author cec
 *  \ingroup lp_solve_interface
 *  \brief Responsibility
 *  \details 
 *  \section ex1 Example
 *  \snippet lp_solve_interface/unit_tests/src/LPSolverTest.cpp LPSolverTest example
 *  \section ex2 Expected output
 *  \snippet lp_solve_interface/unit_tests/src/LPSolverTest.cpp LPSolverTest expected output
 */
class LPSolver
{
    public:
        LPSolver(const std::shared_ptr<OptimizationProblem>& problem);
        LPSolver();
        ~LPSolver();
        LPSolver(const LPSolver& rhs);
        LPSolver& operator=(const LPSolver& rhs);
        OptimizationResult solve();

    private:
        class Impl;
        std::unique_ptr<Impl> pimpl;
};

#endif /* LPSOLVER_HPP_ */
