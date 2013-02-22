/*
 * OptimizationProblem.hpp
 *
 * \date 21 f�vr. 2013, 10:15:54
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
        OptimizationProblem& minimize(const NodePtr& objective_function);
        OptimizationProblem& subject_to(const Parameter& min_bound, const NodePtr& constraint);
        OptimizationProblem& subject_to(const Parameter& min_bound, const NodePtr& constraint, const Parameter& max_bound);
        OptimizationProblem& subject_to(const NodePtr& constraint, const Parameter& max_bound);
        OptimizationProblem& bound_state(const Parameter& min_bound, const StatePtr& state, const Parameter& max_bound);
        OptimizationProblem& bound_state(const StatePtr& state, const Parameter& max_bound);
        OptimizationProblem& bound_state(const Parameter& min_bound, const StatePtr& state);

        StateList get_states() const;
        NodePtr get_objective_function() const;
        void get_constraint_bounds(const size_t& n, double* const gl, double* const gu) const;
        void get_state_bounds(const size_t& n, double* const xl, double* const xu) const;

    private:
        class OptimizationProblem_pimpl;
        std::tr1::shared_ptr<OptimizationProblem_pimpl> pimpl;
};

#endif /* OPTIMIZATIONPROBLEM_HPP_ */