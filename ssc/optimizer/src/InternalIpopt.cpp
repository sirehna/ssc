/*
* InternalIpopt.cpp
*
* \date 25 févr. 2013, 10:03:00
*  \author cec
*/

#include "InternalIpopt.hpp"
#include "State.hpp"
#include "OptimizationResult.hpp"
#include "test_macros.hpp"

InternalIpopt::InternalIpopt(const OptimizationProblem& problem, const bool& show_debug_info) :debugging_on(show_debug_info),
problem_(problem),
objective_function(problem_.get_objective_function()),
constraints(problem_.get_constraints()),
grad_objective_function(problem_.get_grad_objective_function()),
constraint_jacobian(problem_.get_constraint_jacobian()),
hessian(problem_.get_hessian()),
sigma_f(problem_.get_sigma_f()),
lambda(problem_.get_lambda()),
starting_point(std::vector<double>()),
states(problem.get_states())
{
COUT("");
}

void InternalIpopt::set_starting_point(const std::vector<double>& start)
{
    COUT("");
    starting_point = start;
}

/** default destructor */
InternalIpopt::~InternalIpopt()
{
    COUT("");
}

/**@name Overloaded from TNLP */
//@{
/** Method to return some info about the nlp */
bool InternalIpopt::get_nlp_info(Index& n, Index& m, Index& nnz_jac_g,
                        Index& nnz_h_lag, IndexStyleEnum& index_style)
{
    COUT("");
    (void) n;
    (void) m;
    n = states.size();
    m = constraints.size();
    nnz_jac_g = constraint_jacobian.col_index.size();
    nnz_h_lag = hessian.values.size();
    COUT(n);
    COUT(m);
    COUT(nnz_jac_g);
    COUT(nnz_h_lag);
    index_style = C_STYLE;
    COUT("");
    return true;
}

/** Method to return the bounds for my problem */
bool InternalIpopt::get_bounds_info(Index n, Number* x_l, Number* x_u,
                           Index m, Number* g_l, Number* g_u)
{
    COUT("");
    (void) n;
    (void) m;
    (void) g_l;
    (void) g_u;
    (void) x_l;
    (void) x_u;
    problem_.get_state_bounds(n, x_l, x_u);
    //problem_.get_constraint_bounds(m, g_l, g_u);
    COUT("");
    return true;
}

/** Method to return the starting point for the algorithm */
bool InternalIpopt::get_starting_point(Index n, bool init_x, Number* x,
                              bool init_z, Number* z_L, Number* z_U,
                              Index m, bool init_lambda,
                              Number* lambda)
{
    COUT("");
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
    COUT("");
    return true;
}

/** Method to return the objective value */
bool InternalIpopt::eval_f(Index n, const Number* x, bool new_x, Number& obj_value)
{
    COUT("");
    (void) new_x;
    (void) n;
    (void) x;
    (void) new_x;
    /*
    for (size_t i = 0 ; i < (size_t)n ; ++i)
    {
        **states.at(i) = (double)x[i];
    }*/
    (void) obj_value;
    (void) new_x;
    //obj_value = objective_function();
    COUT("");
    return true;
}

/** Method to return the gradient of the objective */
bool InternalIpopt::eval_grad_f(Index n, const Number* x, bool new_x, Number* grad_f)
{
    (void) new_x;
    (void) n;
    (void) x;
    (void) new_x;
    (void) grad_f;
    COUT("");
    /*
    for (size_t i = 0 ; i < (size_t)n ; ++i)
    {
        **states.at(i) = x[i];
    }*/
    (void) new_x;
    //const size_t p = grad_objective_function.index.size();
    /*
    for (size_t i = 0 ; i < p ; ++i)
    {
        grad_f[i] = grad_objective_function.values.at(i)();
    }*/
    COUT("");
    return true;
}

/** Method to return the constraint residuals */
bool InternalIpopt::eval_g(Index n, const Number* x, bool new_x, Index m, Number* g)
{
    (void) new_x;
    (void) n;
    (void) x;
    (void) new_x;
    (void) m;
    (void) g;
    COUT("");
    /*
    for (size_t i = 0 ; i < (size_t)n ; ++i)
    {
        **states.at(i) = x[i];
    }*/
    (void) new_x;
    (void) m;
    //const size_t p = constraints.size();
    /*
    for (size_t i = 0 ; i < p ; ++i)
    {
        g[i] = constraints.at(i)();
    }*/
    COUT("");
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
    COUT("");
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
    /*
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
    }*/
    COUT("");
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
    COUT("");
    (void) new_x;
    (void) new_lambda;
    (void) n;
    (void) x;
    (void) new_x;
    (void) obj_factor;
    (void) m;
    (void) lambda_;
    (void) new_lambda;
    (void) nele_hess;
    (void) iRow;
    (void) jCol;
    (void) values;/*
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
    }*/
    COUT("");
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
    COUT("");
    (void) status;
    (void) n;
    (void) x;
    (void) z_L;
    (void) z_U;
    (void) m;
    (void) g;
    (void) lambda;
    (void) obj_value;
    (void) ip_data;
    (void) ip_cq;
}


OptimizationResult InternalIpopt::get_results() const
{
    COUT("");
    OptimizationResult res;
    const size_t njac = constraint_jacobian.row_index.size();
    res.constraint_jacobian = SparseMatrix(njac);
    /*
    for (size_t i = 0 ; i < njac ; ++i)
    {
        res.constraint_jacobian.add_element_in_row_order(constraint_jacobian.row_index.at(i),
                                                         constraint_jacobian.col_index.at(i),
                                                         constraint_jacobian.values.at(i)());
    }*/
    COUT("");
    return res;
}

