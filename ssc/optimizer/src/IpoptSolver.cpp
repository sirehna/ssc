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
        ~IpoptSolverPimpl(){COUT("");}
        IpoptSolverPimpl(const OptimizationProblem& problem) : internal(new InternalIpopt(problem)),
                                                               nlp(internal.get()),
                                                               app(IpoptApplicationFactory())
        {
            app->Options()->SetNumericValue("tol", 1e-9);
            app->Options()->SetNumericValue("bound_relax_factor", 0);
            app->Options()->SetStringValue("mu_strategy", "adaptive");
            app->Options()->SetIntegerValue("print_level", 0);
            app->Options()->SetIntegerValue("max_iter", 1000);
            const ApplicationReturnStatus status = app->Initialize();

            if (status != Solve_Succeeded)
            {
                printf("\n\n*** Error during initialization!\n");
            }
        }

        OptimizationResult solve(const std::vector<double>& starting_point)
        {
            COUT("");
            internal->set_starting_point(starting_point);
            COUT("");
            const ApplicationReturnStatus status = app->OptimizeTNLP(nlp);
            COUT("");
            OptimizationResult ret = ((InternalIpopt*)GetRawPtr(nlp))->get_results();
            COUT("");
            ret.converged = status == Solve_Succeeded;
            COUT("");
            return ret;
        }

    private:
        IpoptSolverPimpl();
        std::tr1::shared_ptr<InternalIpopt> internal;
        SmartPtr<TNLP> nlp;
        SmartPtr<IpoptApplication> app;
};



IpoptSolver::IpoptSolver(const OptimizationProblem& problem) : pimpl(new IpoptSolverPimpl(problem))
{
}

OptimizationResult IpoptSolver::solve(const std::vector<double>& starting_point)
{
    COUT("");
    return pimpl->solve(starting_point);
}
