/*
 * OptimizationProblem.hpp
 *
 * \date 21 févr. 2013, 10:15:54
 *  \author cec
 */

#ifndef OPTIMIZATIONPROBLEM_HPP_
#define OPTIMIZATIONPROBLEM_HPP_

#define INFTY 2e19

#include "FunctorAlgebra.hpp"
#include "Sum.hpp"
#include "Multiply.hpp"
#include "Pow.hpp"
#include "Difference.hpp"
#include "GradHes.hpp"

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/OptimizationProblemTest.cpp OptimizationProblemTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/OptimizationProblemTest.cpp OptimizationProblemTest expected output
 */

#include "Exception.hpp"

class OptimizationProblemException : public Exception
{
    public:
        OptimizationProblemException(const char* s) :
                Exception(s)
        {
        }
};

class OptimizationProblem
{
    public:
        OptimizationProblem();
        virtual ~OptimizationProblem();
        OptimizationProblem& minimize(const NodePtr& objective_function);
        OptimizationProblem& maximize(const NodePtr& objective_function);
        OptimizationProblem& subject_to(const Parameter& min_bound, const NodePtr& constraint);
        OptimizationProblem& subject_to(const Parameter& min_bound, const NodePtr& constraint, const Parameter& max_bound);
        OptimizationProblem& subject_to(const NodePtr& constraint, const Parameter& max_bound);
        OptimizationProblem& bound_state(const Parameter& min_bound, const StatePtr& state, const Parameter& max_bound);
        OptimizationProblem& bound_state(const StatePtr& state, const Parameter& max_bound);
        OptimizationProblem& bound_state(const Parameter& min_bound, const StatePtr& state);
        OptimizationProblem& binary(const StatePtr& state);
        OptimizationProblem& integer(const StatePtr& state);

        bool has_binary_variables() const;
        bool has_integer_variables() const;
        bool has_continuous_variables() const;

        StateList get_states() const;
        std::function<double()> get_objective_function() const;
        std::vector<std::function<double()> > get_constraints() const;
        Grad get_grad_objective_function() const;
        FunctionMatrix get_constraint_jacobian() const;
        FunctionMatrix get_hessian() const;
        Parameter get_sigma_f() const;
        std::vector<Parameter> get_lambda() const;
        void get_constraint_bounds(const size_t& n, double* const gl, double* const gu) const;
        void get_state_bounds(const size_t& n, double* const xl, double* const xu) const;
        friend ::std::ostream& operator<<(::std::ostream& os, const OptimizationProblem& pb);
        void reset_state_bounds();
        bool is_a_minimization_problem() const;
        std::vector<size_t> get_index_of_binary_variables() const;
        std::vector<size_t> get_index_of_integer_variables() const;

    private:
        void check_state_for_bound_setting(const StatePtr& state) const;
        class OptimizationProblem_pimpl;
        std::tr1::shared_ptr<OptimizationProblem_pimpl> pimpl;
};

::std::ostream& operator<<(::std::ostream& os, const OptimizationProblem& pb);

#endif /* OPTIMIZATIONPROBLEM_HPP_ */
