/*
 * LPSolver.hpp
 *
 * \date 20 nov. 2013, 14:01:21
 *  \author cec
 */

#ifndef LPSOLVER_HPP_
#define LPSOLVER_HPP_

<<<<<<< HEAD
#include <tr1/memory>
=======
>>>>>>> Stubbed lpsolve_interface
#include <memory>
#include "OptimizationResult.hpp"

class OptimizationProblem;

<<<<<<< HEAD

struct LPSolverParameters
{
	LPSolverParameters() : verbose_level(0){}
	size_t verbose_level;
};

=======
>>>>>>> Stubbed lpsolve_interface
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
<<<<<<< HEAD
        LPSolver(const std::tr1::shared_ptr<OptimizationProblem>& problem, const LPSolverParameters& par = LPSolverParameters());
=======
        LPSolver(const std::shared_ptr<OptimizationProblem>& problem);
>>>>>>> Stubbed lpsolve_interface
        LPSolver();
        ~LPSolver();
        LPSolver(const LPSolver& rhs);
        LPSolver& operator=(const LPSolver& rhs);
<<<<<<< HEAD
        OptimizationResult solve(const std::vector<double>& x0);
=======
        OptimizationResult solve();
>>>>>>> Stubbed lpsolve_interface

    private:
        class Impl;
        std::unique_ptr<Impl> pimpl;
};

#endif /* LPSOLVER_HPP_ */
