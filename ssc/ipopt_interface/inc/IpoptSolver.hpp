/*
 * IpoptSolver.hpp
 *
 * \date 22 févr. 2013, 15:28:59
 *  \author cec
 */

#ifndef IPOPTSOLVER_HPP_
#define IPOPTSOLVER_HPP_

#include "tr1_macros.hpp"
#include TR1INC(memory)
#include <vector>
#include "IpoptParameters.hpp"

struct OptimizationResult;
class OptimizationProblem;



/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet ipopt_interface/unit_tests/src/IpoptSolverTest.cpp IpoptSolverTest example
 *  \section ex2 Expected output
 *  \snippet ipopt_interface/unit_tests/src/IpoptSolverTest.cpp IpoptSolverTest expected output
 */

class IpoptSolver
{
    public:
        IpoptSolver(const std::tr1::shared_ptr<OptimizationProblem>& problem, const IpoptParameters& parameters = IpoptParameters());
        IpoptSolver();
        OptimizationResult solve(const std::vector<double>& starting_point);

    private:
        class IpoptSolverPimpl;
        std::tr1::shared_ptr<IpoptSolverPimpl> pimpl;
};

#endif /* IPOPTSOLVER_HPP_ */
