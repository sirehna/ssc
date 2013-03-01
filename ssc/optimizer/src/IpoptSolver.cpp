/*
 * IpoptSolver.cpp
 *
 * \date 22 févr. 2013, 15:28:59
 *  \author cec
 */

#include "Grad.hpp"
#include "FunctionMatrix.hpp"
#include "IpoptSolver.hpp"
#include "OptimizationResult.hpp"
#include "OptimizationProblem.hpp"
#include "Parameter.hpp"
#include "State.hpp"
#include "InternalIpopt.hpp"
#include "IpIpoptApplication.hpp"

#include "test_macros.hpp"

class IpoptSolver::IpoptSolverPimpl
{
    public:
        ~IpoptSolverPimpl(){}
        IpoptSolverPimpl(const std::tr1::shared_ptr<OptimizationProblem>& problem, const IpoptParameters& parameters) : nlp(new InternalIpopt(problem, parameters)),
                                                               app(IpoptApplicationFactory())
        {
            app->Options()->SetNumericValue("tol", parameters.tolerance);
            app->Options()->SetNumericValue("bound_relax_factor", parameters.bound_relaxation_factor);
            app->Options()->SetStringValue("mu_strategy", parameters.mu_strategy);
            app->Options()->SetIntegerValue("print_level", parameters.print_level);
            app->Options()->SetIntegerValue("max_iter", parameters.maximum_number_of_iterations);
            const ApplicationReturnStatus status = app->Initialize();

            if (status != Solve_Succeeded)
            {
                printf("\n\n*** Error during initialization!\n");
            }
        }

        OptimizationResult solve(const std::vector<double>& starting_point)
        {
            (dynamic_cast<InternalIpopt*>(GetRawPtr(nlp)))->set_starting_point(starting_point);
            const ApplicationReturnStatus status = app->OptimizeTNLP(nlp);
            OptimizationResult ret = (dynamic_cast<InternalIpopt*>(GetRawPtr(nlp)))->get_results();
            ret.converged = status == Solve_Succeeded;
            return ret;
        }

    private:
        IpoptSolverPimpl();
        SmartPtr<TNLP> nlp;
        SmartPtr<IpoptApplication> app;
};



IpoptSolver::IpoptSolver(const OptimizationProblem& problem, const IpoptParameters& parameters) :
        pimpl(new IpoptSolverPimpl(std::tr1::shared_ptr<OptimizationProblem>(new OptimizationProblem(problem)),parameters))
{
}

OptimizationResult IpoptSolver::solve(const std::vector<double>& starting_point)
{
    return pimpl->solve(starting_point);
}
