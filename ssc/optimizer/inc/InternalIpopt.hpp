/*
 * InternalIpopt.hpp
 *
 * \date 25 févr. 2013, 10:03:00
 *  \author cec
 */

#ifndef INTERNALIPOPT_HPP_
#define INTERNALIPOPT_HPP_

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/InternalIpoptTest.cpp InternalIpoptTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/InternalIpoptTest.cpp InternalIpoptTest expected output
 */

#include <cstddef> /* most likely Ipopt has C++ code that includes some
    STL headers and relies on them bringing in <stddef.h>
    and is using ::ptrdiff_t, ::size_t, offsetof or NULL
    macros.  The STL headers in gcc 4.6 onwards just declare std::ptrdiff_t
    and std::size_t itself when needed, and no longer bring
    in <stddef.h>, so if you use the global namespace types
    from stddef.h or offsetof/NULL, just include <cstddef>
    explicitly.*/
#include "IpTNLP.hpp"
#include "OptimizationProblem.hpp"
#include "Grad.hpp"
#include "FunctionMatrix.hpp"
#include "Parameter.hpp"

using namespace Ipopt;

class OptimizationResult;

class InternalIpopt : public TNLP
{
    public:
      /** default constructor */
        InternalIpopt(const OptimizationProblem& problem, const bool& show_debug_info = false);

       void set_starting_point(const std::vector<double>& start);

        /** default destructor */
      virtual ~InternalIpopt();

      /**@name Overloaded from TNLP */
      //@{
      /** Method to return some info about the nlp */
      virtual bool get_nlp_info(Index& n, Index& m, Index& nnz_jac_g,
                                Index& nnz_h_lag, IndexStyleEnum& index_style);

      /** Method to return the bounds for my problem */
      virtual bool get_bounds_info(Index n, Number* x_l, Number* x_u,
                                   Index m, Number* g_l, Number* g_u);


      /** Method to return the starting point for the algorithm */
      virtual bool get_starting_point(Index n, bool init_x, Number* x,
                                      bool init_z, Number* z_L, Number* z_U,
                                      Index m, bool init_lambda,
                                      Number* lambda);

      /** Method to return the objective value */
      virtual bool eval_f(Index n, const Number* x, bool new_x, Number& obj_value);

      /** Method to return the gradient of the objective */
      virtual bool eval_grad_f(Index n, const Number* x, bool new_x, Number* grad_f);

      /** Method to return the constraint residuals */
      virtual bool eval_g(Index n, const Number* x, bool new_x, Index m, Number* g);

      /** Method to return:
       *   1) The structure of the jacobian (if "values" is NULL)
       *   2) The values of the jacobian (if "values" is not NULL)
       */
      virtual bool eval_jac_g(Index n, const Number* x, bool new_x,
                              Index m, Index nele_jac, Index* iRow, Index *jCol,
                              Number* values);
      /** Method to return:
       *   1) The structure of the hessian of the lagrangian (if "values" is NULL)
       *   2) The values of the hessian of the lagrangian (if "values" is not NULL)
       */
      virtual bool eval_h(Index n, const Number* x, bool new_x,
                          Number obj_factor, Index m, const Number* lambda_,
                          bool new_lambda, Index nele_hess, Index* iRow,
                          Index* jCol, Number* values);
      //@}

      /** @name Solution Methods */
      //@{
      /** This method is called when the algorithm is complete so the TNLP can store/write the solution */
      virtual void finalize_solution(SolverReturn status,
                                     Index n, const Number* x, const Number* z_L, const Number* z_U,
                                     Index m, const Number* g, const Number* lambda,
                                     Number obj_value,
                     const IpoptData* ip_data,
                     IpoptCalculatedQuantities* ip_cq);      //@}

      OptimizationResult get_results() const;

    private:
      /**@name Methods to block default compiler methods.
       * The compiler automatically generates the following three methods.
       *  Since the default compiler implementation is generally not what
       *  you want (for all but the most simple classes), we usually
       *  put the declarations of these methods in the private section
       *  and never implement them. This prevents the compiler from
       *  implementing an incorrect "default" behavior without us
       *  knowing. (See Scott Meyers book, "Effective C++")
       *
       */
      //@{
      InternalIpopt();
      InternalIpopt(const InternalIpopt&);
      InternalIpopt& operator=(const InternalIpopt&);

      bool debugging_on;
      OptimizationProblem problem_;
      std::function<double()> objective_function;
      std::vector<std::function<double()> > constraints;
      Grad grad_objective_function;
      FunctionMatrix constraint_jacobian;
      FunctionMatrix hessian;
      Parameter sigma_f;
      std::vector<Parameter> lambda;
      std::vector<double> starting_point;
      StateList states;


      //@}
};


#endif /* INTERNALIPOPT_HPP_ */
