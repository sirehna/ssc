/*
* InternalIpopt.cpp
*
* \date 25 févr. 2013, 10:03:00
*  \author cec
*/

#include "InternalIpopt.hpp"
#include "State.hpp"
#include "IpIpoptData.hpp"
#include "IpoptParameters.hpp"


#include "test_macros.hpp"

InternalIpopt::InternalIpopt(const std::tr1::shared_ptr<OptimizationProblem>& problem, const IpoptParameters& parameters) :
problem_(problem),
objective_function(problem_->get_objective_function()),
constraints(problem_->get_constraints()),
grad_objective_function(problem_->get_grad_objective_function()),
constraint_jacobian(problem_->get_constraint_jacobian()),
hessian(problem_->get_hessian()),
sigma_f(problem_->get_sigma_f()),
lambda(problem_->get_lambda()),
starting_point(std::vector<double>()),
states(problem_->get_states()),
results(OptimizationResult()),
trace_function_calls(parameters.trace_function_calls)
{
}

void InternalIpopt::set_starting_point(const std::vector<double>& start)
{
    if (trace_function_calls) std::cout << "entering InternalIpopt::set_starting_point" << std::endl;
    starting_point = start;
    if (trace_function_calls) std::cout << "exiting InternalIpopt::set_starting_point" << std::endl;
}

/** default destructor */
InternalIpopt::~InternalIpopt()
{
    if (trace_function_calls) std::cout << "entering InternalIpopt::~InternalIpopt()" << std::endl;
    if (trace_function_calls) std::cout << "exiting InternalIpopt::~InternalIpopt()" << std::endl;
}

/**@name Overloaded from TNLP */
//@{
/** Method to return some info about the nlp */
bool InternalIpopt::get_nlp_info(Index& n, Index& m, Index& nnz_jac_g,
                        Index& nnz_h_lag, IndexStyleEnum& index_style)
{
    if (trace_function_calls) std::cout << "entering InternalIpopt::get_nlp_info" << std::endl;
    (void) n;
    (void) m;
    n = states.size();
    m = constraints.size();
    nnz_jac_g = constraint_jacobian.col_index.size();
    nnz_h_lag = hessian.values.size();
    index_style = C_STYLE;
    if (trace_function_calls) std::cout << "exiting InternalIpopt::get_nlp_info" << std::endl;
    return true;
}

/** Method to return the bounds for my problem */
bool InternalIpopt::get_bounds_info(Index n, Number* x_l, Number* x_u,
                           Index m, Number* g_l, Number* g_u)
{
    if (trace_function_calls) std::cout << "entering InternalIpopt::get_bounds_info" << std::endl;
    (void) n;
    (void) m;
    (void) g_l;
    (void) g_u;
    (void) x_l;
    (void) x_u;
    problem_->get_state_bounds(n, x_l, x_u);
    problem_->get_constraint_bounds(m, g_l, g_u);
    if (trace_function_calls) std::cout << "exiting InternalIpopt::get_bounds_info" << std::endl;
    return true;
}

/** Method to return the starting point for the algorithm */
bool InternalIpopt::get_starting_point(Index n, bool init_x, Number* x,
                              bool init_z, Number* z_L, Number* z_U,
                              Index m, bool init_lambda,
                              Number* lambda)
{
    if (trace_function_calls) std::cout << "entering InternalIpopt::get_starting_point" << std::endl;
    (void) n;
    (void) x;
    (void) m;
    for (size_t i = 0 ; i < (size_t)n ; ++i)
    {
        x[i] = starting_point.at(i);
    }
    (void) init_x;
    (void) init_z;
    (void) z_L;
    (void) z_U;
    (void) m;
    (void) init_lambda;
    (void) lambda;
    if (trace_function_calls) std::cout << "exiting InternalIpopt::get_starting_point" << std::endl;
    return true;
}

/** Method to return the objective value */
bool InternalIpopt::eval_f(Index n, const Number* x, bool new_x, Number& obj_value)
{
    if (trace_function_calls) std::cout << "entering InternalIpopt::eval_f" << std::endl;
    (void) new_x;
    (void) n;
    (void) x;
    (void) new_x;

    for (size_t i = 0 ; i < (size_t)n ; ++i)
    {
        **states.at(i) = (double)x[i];
    }
    (void) obj_value;
    (void) new_x;
    obj_value = objective_function();
    if (trace_function_calls) std::cout << "exiting InternalIpopt::eval_f" << std::endl;
    return true;
}

/** Method to return the gradient of the objective */
bool InternalIpopt::eval_grad_f(Index n, const Number* x, bool new_x, Number* grad_f)
{
    if (trace_function_calls) std::cout << "entering InternalIpopt::eval_grad_f" << std::endl;
    (void) new_x;
    (void) n;
    (void) x;
    (void) new_x;
    (void) grad_f;
    for (size_t i = 0 ; i < (size_t)n ; ++i)
    {
        **states.at(i) = x[i];
    }
    (void) new_x;
    const size_t p = grad_objective_function.index.size();

    for (size_t i = 0 ; i < p ; ++i)
    {
        grad_f[i] = grad_objective_function.values.at(i)();
    }
    if (trace_function_calls) std::cout << "exiting InternalIpopt::eval_grad_f" << std::endl;
    return true;
}

/** Method to return the constraint residuals */
bool InternalIpopt::eval_g(Index n, const Number* x, bool new_x, Index m, Number* g)
{
    if (trace_function_calls) std::cout << "entering InternalIpopt::eval_g" << std::endl;
    (void) new_x;
    (void) n;
    (void) x;
    (void) new_x;
    (void) m;
    (void) g;

    for (size_t i = 0 ; i < (size_t)n ; ++i)
    {
        **states.at(i) = x[i];
    }
    (void) new_x;
    (void) m;
    const size_t p = constraints.size();

    for (size_t i = 0 ; i < p ; ++i)
    {
        g[i] = constraints.at(i)();
    }
    if (trace_function_calls) std::cout << "exiting InternalIpopt::eval_g" << std::endl;
    return true;
}

/** Method to return:
*   1) The structure of the jacobian (if "values" is NULL)
*   2) The values of the jacobian (if "values" is not NULL)
*/
bool InternalIpopt::eval_jac_g(Index n, const Number* x, bool new_x,
                      Index m, Index nele_jac, Index* iRow, Index *jCol,
                      Number* values)
{
    if (trace_function_calls) std::cout << "entering InternalIpopt::eval_jac_g" << std::endl;
    (void) new_x;
    (void) m;
    (void) n;
    (void) x;
    (void) new_x;
    (void) m;
    (void) iRow;
    (void) jCol;
    (void) values;
    (void) nele_jac;

    if (values == NULL)
    {
        for (size_t i = 0 ; i < (size_t)nele_jac ; ++i)
        {
            iRow[i] = constraint_jacobian.row_index.at(i);
            jCol[i] = constraint_jacobian.col_index.at(i);
        }
    }
    else
    {
        for (size_t i = 0 ; i < (size_t)n ; ++i)
        {
            **states.at(i) = x[i];
        }
        for (size_t i = 0 ; i < (size_t)nele_jac ; ++i)
        {
            values[i] = constraint_jacobian.values.at(i)();
        }
    }
    if (trace_function_calls) std::cout << "exiting InternalIpopt::eval_jac_g" << std::endl;
    return true;
}

/** Method to return:
*   1) The structure of the hessian of the lagrangian (if "values" is NULL)
*   2) The values of the hessian of the lagrangian (if "values" is not NULL)
*/
bool InternalIpopt::eval_h(Index n, const Number* x, bool new_x,
                  Number obj_factor, Index m, const Number* lambda_,
                  bool new_lambda, Index nele_hess, Index* iRow,
                  Index* jCol, Number* values)
{
    if (trace_function_calls) std::cout << "entering InternalIpopt::eval_h" << std::endl;
    (void) new_x;
    (void) new_lambda;
    (void) new_x;
    (void) new_lambda;
    if (values == NULL)
    {
        for (size_t i = 0 ; i < (size_t)nele_hess ; ++i)
        {
            iRow[i] = hessian.row_index.at(i);
            jCol[i] = hessian.col_index.at(i);
        }
    }
    else
    {
        *sigma_f = obj_factor;
        for (size_t j = 0 ; j < (size_t)m ; ++j)
        {
            *lambda.at(j) = lambda_[j];
        }
        for (size_t i = 0 ; i < (size_t)n ; ++i)
        {
            **states.at(i) = x[i];
        }
        for (size_t i = 0 ; i < (size_t)nele_hess ; ++i)
        {
            values[i] = hessian.values.at(i)();
        }
    }
    if (trace_function_calls) std::cout << "exiting InternalIpopt::eval_h" << std::endl;
    return true;
}

//@}

/** @name Solution Methods */
//@{
/** This method is called when the algorithm is complete so the TNLP can store/write the solution */
void InternalIpopt::finalize_solution(SolverReturn status,
                             Index n, const Number* x, const Number* z_L, const Number* z_U,
                             Index m, const Number* g, const Number* lambda,
                             Number obj_value,
             const IpoptData* ip_data,
             IpoptCalculatedQuantities* ip_cq)
{
    if (trace_function_calls) std::cout << "entering InternalIpopt::finalize_solution" << std::endl;
    (void) z_L;
    (void) z_U;
    (void) lambda;
    (void) obj_value;
    (void) ip_cq;

    const size_t njac = constraint_jacobian.row_index.size();
    results.constraint_jacobian = SparseMatrix(njac);

    for (size_t i = 0 ; i < njac ; ++i)
    {
        results.constraint_jacobian.add_element_in_row_order(constraint_jacobian.row_index.at(i),
                                                         constraint_jacobian.col_index.at(i),
                                                         constraint_jacobian.values.at(i)());
    }
    switch (status)
    {
        case SUCCESS:
            results.converged = true;
            break;
        case STOP_AT_ACCEPTABLE_POINT:
            results.converged = true;
            break;
        default:
            results.converged = false;
            break;
    }

    results.state_values                       = std::vector<double>(x, x+n);
    results.value_of_the_objective_function    = objective_function();
    results.constraint_values                  = std::vector<double>(g, g+m);
    results.nb_of_iterations                   = ip_data ? (size_t)ip_data->iter_count() : 0;
    results.total_time_needed_for_optimization = ip_data ? (double)(const_cast<IpoptData*>(ip_data))->TimingStats().OverallAlgorithm().TotalCpuTime() : 0;
    if (trace_function_calls) std::cout << "exiting InternalIpopt::finalize_solution" << std::endl;
}


OptimizationResult InternalIpopt::get_results() const
{
    if (trace_function_calls) std::cout << "entering InternalIpopt::get_results" << std::endl;
    if (trace_function_calls) std::cout << "exiting InternalIpopt::get_results" << std::endl;
    return results;
}

