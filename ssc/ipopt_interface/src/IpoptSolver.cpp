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
#include "IpoptSolverException.hpp"

class IpoptSolver::IpoptSolverPimpl
{
    public:
        ~IpoptSolverPimpl(){}
        IpoptSolverPimpl(const std::tr1::shared_ptr<OptimizationProblem>& problem, IpoptParameters parameters) : nlp(new InternalIpopt(problem, parameters)),
                                                               app(IpoptApplicationFactory())
        {
            if (problem->has_binary_variables())
            {
                THROW(__PRETTY_FUNCTION__, IpoptSolverException, "There are binary (0/1) variables in the optimization problem: solver Ipopt can only be used on continuous problems");
            }
            if (problem->has_integer_variables())
            {
                THROW(__PRETTY_FUNCTION__, IpoptSolverException, "There are integer variables in the optimization problem: solver Ipopt can only be used on continuous problems");
            }
            app->Options()->SetNumericValue("tol", parameters.tolerance);
            app->Options()->SetNumericValue("bound_relax_factor", parameters.bound_relaxation_factor);
            app->Options()->SetNumericValue("obj_scaling_factor", problem->is_a_minimization_problem() ? 1 : -1);
            app->Options()->SetStringValue("mu_strategy", parameters.mu_strategy);

            if (not(parameters.check_first_derivative||parameters.check_second_derivative))
            {
                app->Options()->SetStringValue("derivative_test", "none");
            }
            if (not(parameters.check_first_derivative)&&parameters.check_second_derivative)
            {
                app->Options()->SetStringValue("derivative_test", "only-second-order");
            }
            if (parameters.check_first_derivative&&not(parameters.check_second_derivative))
            {
                app->Options()->SetStringValue("derivative_test", "first-order");
            }
            if (parameters.check_first_derivative&&parameters.check_second_derivative)
            {
                app->Options()->SetStringValue("derivative_test", "second-order");

            }
            if (parameters.check_first_derivative||parameters.check_second_derivative)
            {
                app->Options()->SetStringValue("derivative_test_print_all", "yes");
                if (parameters.print_level<4) parameters.print_level = 4;
                app->Options()->SetNumericValue("derivative_test_perturbation", 1e-8);
                app->Options()->SetNumericValue("derivative_test_tol", 1e-4);
                app->Options()->SetNumericValue("point_perturbation_radius", 0);
            }

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
            ret.converged = (status == Solve_Succeeded) || (status == Solved_To_Acceptable_Level) || (status == Feasible_Point_Found);
            return ret;
        }

    private:
        IpoptSolverPimpl();
        SmartPtr<TNLP> nlp;
        SmartPtr<IpoptApplication> app;
};



IpoptSolver::IpoptSolver(const std::tr1::shared_ptr<OptimizationProblem>& problem, const IpoptParameters& parameters) :
        pimpl(new IpoptSolverPimpl(problem, parameters))
{
}

IpoptSolver::IpoptSolver() : pimpl(std::tr1::shared_ptr<IpoptSolverPimpl>())
{

}


OptimizationResult IpoptSolver::solve(const std::vector<double>& starting_point)
{
    return pimpl->solve(starting_point);
}
