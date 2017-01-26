/*
 * LPSolver.hpp
 *
 * \date 20 nov. 2013, 14:01:21
 *  \author cec
 */

#ifndef LPSOLVER_HPP_
#define LPSOLVER_HPP_

#include <tr1/memory>
#include <memory>
#include "OptimizationResult.hpp"

class OptimizationProblem;


struct LPSolverParameters
{
    LPSolverParameters() : verbose_level(0){}
    size_t verbose_level;
};

/** \author cec
 *  \ingroup lp_solve_interface
 *  \brief Responsibility
 *  \details
 *  \section ex1 Example
 *  \snippet lpsolve_interface/unit_tests/src/LPSolverTest.cpp LPSolverTest example
 *  \section ex2 Expected output
 *  \snippet lpsolve_interface/unit_tests/src/LPSolverTest.cpp LPSolverTest expected output
 */
class LPSolver
{
    public:
        LPSolver(const std::tr1::shared_ptr<OptimizationProblem>& problem, const LPSolverParameters& par = LPSolverParameters());
        LPSolver();
        ~LPSolver();
        LPSolver(const LPSolver& rhs);
        LPSolver& operator=(const LPSolver& rhs);
        OptimizationResult solve(const std::vector<double>& x0);

    private:
        class Impl;
        std::unique_ptr<Impl> pimpl;
};

#endif /* LPSOLVER_HPP_ */
