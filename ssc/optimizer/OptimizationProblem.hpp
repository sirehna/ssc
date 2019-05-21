/*
 * OptimizationProblem.hpp
 *
 * \date 21 févr. 2013, 10:15:54
 * \author cec
 */

#ifndef OPTIMIZATIONPROBLEM_HPP_
#define OPTIMIZATIONPROBLEM_HPP_

#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"
#include "ssc/functors_for_optimizer/Sum.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/functors_for_optimizer/Pow.hpp"
#include "ssc/functors_for_optimizer/Difference.hpp"
#include "ssc/functors_for_optimizer/GradHes.hpp"

#define INFTY 2e19

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/OptimizationProblemTest.cpp OptimizationProblemTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/OptimizationProblemTest.cpp OptimizationProblemTest expected output
 */

#include "ssc/exception_handling/Exception.hpp"

namespace ssc
{
    namespace optimizer
    {
        class OptimizationProblemException : public ssc::exception_handling::Exception
        {
            public:
                OptimizationProblemException(const std::string& message, const std::string& file, const std::string& function, const unsigned int line) :
                    Exception(message, file, function, line)
                {
                }
        };

        class OptimizationProblem
        {
            public:
                OptimizationProblem();
                virtual ~OptimizationProblem();
                OptimizationProblem& minimize(const ssc::functors_for_optimizer::NodePtr& objective_function);
                OptimizationProblem& maximize(const ssc::functors_for_optimizer::NodePtr& objective_function);
                OptimizationProblem& subject_to(const ssc::functors_for_optimizer::Parameter& min_bound, const ssc::functors_for_optimizer::NodePtr& constraint);
                OptimizationProblem& subject_to(const ssc::functors_for_optimizer::Parameter& min_bound, const ssc::functors_for_optimizer::NodePtr& constraint, const ssc::functors_for_optimizer::Parameter& max_bound);
                OptimizationProblem& subject_to(const ssc::functors_for_optimizer::NodePtr& constraint, const ssc::functors_for_optimizer::Parameter& max_bound);
                OptimizationProblem& bound_state(const ssc::functors_for_optimizer::Parameter& min_bound, const ssc::functors_for_optimizer::StatePtr& state, const ssc::functors_for_optimizer::Parameter& max_bound);
                OptimizationProblem& bound_state(const ssc::functors_for_optimizer::StatePtr& state, const ssc::functors_for_optimizer::Parameter& max_bound);
                OptimizationProblem& bound_state(const ssc::functors_for_optimizer::Parameter& min_bound, const ssc::functors_for_optimizer::StatePtr& state);
                OptimizationProblem& binary(const ssc::functors_for_optimizer::StatePtr& state);
                OptimizationProblem& integer(const ssc::functors_for_optimizer::StatePtr& state);

                bool has_binary_variables() const;
                bool has_integer_variables() const;
                bool has_continuous_variables() const;

                ssc::functors_for_optimizer::StateList get_states() const;
                std::function<double()> get_objective_function() const;
                std::vector<std::function<double()> > get_constraints() const;
                ssc::functors_for_optimizer::Grad<std::function<double()> > get_grad_objective_function() const;
                ssc::functors_for_optimizer::FunctionMatrix<std::function<double()> > get_constraint_jacobian() const;
                ssc::functors_for_optimizer::FunctionMatrix<std::function<double()> > get_hessian() const;
                ssc::functors_for_optimizer::Parameter get_sigma_f() const;
                std::vector<ssc::functors_for_optimizer::Parameter> get_lambda() const;
                void get_constraint_bounds(const size_t& n, double* const gl, double* const gu) const;
                void get_state_bounds(const size_t& n, double* const xl, double* const xu) const;
                friend ::std::ostream& operator<<(::std::ostream& os, const OptimizationProblem& pb);
                void reset_state_bounds();
                void clear_constraints();
                bool is_a_minimization_problem() const;
                std::vector<size_t> get_index_of_binary_variables() const;
                std::vector<size_t> get_index_of_integer_variables() const;

            private:
                void check_state_for_bound_setting(const ssc::functors_for_optimizer::StatePtr& state) const;
                class OptimizationProblem_pimpl;
                TR1(shared_ptr)<OptimizationProblem_pimpl> pimpl;
        };

        ::std::ostream& operator<<(::std::ostream& os, const OptimizationProblem& pb);
    }
}
#endif /* OPTIMIZATIONPROBLEM_HPP_ */
