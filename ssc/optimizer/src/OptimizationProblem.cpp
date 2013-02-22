/*
 * OptimizationProblem.cpp
 *
 * \date 21 févr. 2013, 10:15:54
 *  \author cec
 */

#include "OptimizationProblem.hpp"
#include "Parameter.hpp"
#include "Null.hpp"

template <class T> class MinMax
{
    public:
        MinMax(const Parameter& min_, const T& val_, const Parameter& max_) : min(min_), max(max_), val(val_)
        {

        }
        Parameter min;
        Parameter max;
        T val;
    private:
        MinMax();
};

class OptimizationProblem::OptimizationProblem_pimpl
{
    public:
        OptimizationProblem_pimpl() : objective_function(Null().clone()),
                                      constraints(std::vector<MinMax<NodePtr> >()),
                                      states(StateList())
        {

        }
        NodePtr objective_function;
        std::vector<NodePtr> get_constraints() const
        {
            std::vector<NodePtr> ret;
            for (auto c = constraints.begin() ; c != constraints.end() ; ++c)
            {
                ret.push_back(c->val);
            }
            return ret;
        }

        double get_max_bound() const
        {
            return 2e19;
        }

        double get_min_bound() const
        {
            return -get_max_bound();
        }

        std::vector<MinMax<NodePtr> > constraints;
        StateList states;
};

OptimizationProblem::OptimizationProblem() : pimpl(new OptimizationProblem_pimpl())
{
}

OptimizationProblem& OptimizationProblem::minimize(const NodePtr& objective_function)
{
    pimpl->objective_function = objective_function;
    pimpl->states = ::get_states(pimpl->objective_function, pimpl->get_constraints());
    return *this;
}

OptimizationProblem& OptimizationProblem::subject_to(const double& min_bound, const NodePtr& constraint)
{
    pimpl->constraints.push_back(MinMax<NodePtr>(Parameter(min_bound),constraint,Parameter(pimpl->get_max_bound())));
    pimpl->states = ::get_states(pimpl->objective_function, pimpl->get_constraints());
    return *this;
}

OptimizationProblem& OptimizationProblem::subject_to(const double& min_bound, const NodePtr& constraint, const double& max_bound)
{
    pimpl->constraints.push_back(MinMax<NodePtr>(Parameter(min_bound),constraint,Parameter(max_bound)));
    pimpl->states = ::get_states(pimpl->objective_function, pimpl->get_constraints());
    return *this;
}

StateList OptimizationProblem::get_states() const
{
    return pimpl->states;
}

NodePtr OptimizationProblem::get_objective_function() const
{
    return pimpl->objective_function;
}

void OptimizationProblem::get_constraint_bounds(double* const gl, double* const gu) const
{
    size_t i = 0;
    if (gl == NULL)
    {
        THROW("OptimizationProblem::get_constraint_bounds(double* const, double* const)", OptimizationProblemException, "gl == NULL");
    }
    if (gu == NULL)
    {
        THROW("OptimizationProblem::get_constraint_bounds(double* const, double* const)", OptimizationProblemException, "gu == NULL");
    }
    for (auto it = pimpl->constraints.begin() ; it != pimpl->constraints.end() ; ++it)
    {
        gl[i] = *(it->min);
        gu[i++] = *(it->max);
    }
}
