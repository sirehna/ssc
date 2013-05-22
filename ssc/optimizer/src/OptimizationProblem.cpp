/*
 * OptimizationProblem.cpp
 *
 * \date 21 févr. 2013, 10:15:54
 *  \author cec
 */
#include <map>
#include <algorithm>    // std::find
#include "OptimizationProblem.hpp"
#include "Parameter.hpp"
#include "Null.hpp"
#include "State.hpp"
#include "Serialize.hpp"
#include "GradHes.hpp"
#include "Grad.hpp"
#include "FunctionMatrix.hpp"

template <class T> class MinMaxList
{
    public:
        MinMaxList() : min(std::map<std::string,Parameter> ()),
                       max(std::map<std::string,Parameter>()),
                       val(std::vector<T>()){}

        std::vector<T> get_vals() const
        {
            std::vector<T> ret;
            for (auto c = val.begin() ; c != val.end() ; ++c)
            {
                ret.push_back(*c);
            }
            return ret;
        }

        void add_to_val(const T& v)
        {
            const bool already_present = bounds_already_set(v);
            if (already_present)
            {
                THROW("add_to_val(const T&)", OptimizationProblemException, "Attempting to specify bounds for the same constraint twice");
            }
            val.push_back(v);
        }

        void push_back(const Parameter& min_, const T& val_, const Parameter& max_)
        {
            add_to_val(val_);
            min[get_string(val_)] = min_;
            max[get_string(val_)] = max_;
        }

        void push_back(const Parameter& min_, const T& val_)
        {
            add_to_val(val_);
            min[get_string(val_)] = min_;
        }

        void push_back(const T& val_, const Parameter& max_)
        {
            add_to_val(val_);
            max[get_string(val_)] = max_;
        }

        double get_max_bound() const
        {
            return INFTY;
        }

        double get_min_bound() const
        {
            return -get_max_bound();
        }

        void get_bounds(const size_t& n, double* const l, double* const u) const
        {
            if (l == NULL)
            {
                THROW("OptimizationProblem::OptimizationProblem_pimpl::get_bounds(double* const, double* const)", OptimizationProblemException, "l == NULL");
            }
            if (u == NULL)
            {
                THROW("OptimizationProblem::OptimizationProblem_pimpl::get_bounds(double* const, double* const)", OptimizationProblemException, "u == NULL");
            }
            if (n!= val.size())
            {
                THROW("get_bounds(const size_t&, double* const, double* const)", OptimizationProblemException, "Invalid size");
            }
            size_t i = 0;
            for (auto v = val.begin() ; v != val.end() ; ++v)
            {
                auto it_min = min.find(get_string(*v));
                auto it_max = max.find(get_string(*v));
                bool found_value_in_min_map = not(it_min==min.end());
                bool found_value_in_max_map = not(it_max==max.end());
                l[i]   = found_value_in_min_map ? (it_min->second).get_lambda()() : get_min_bound();
                u[i++] = found_value_in_max_map ? (it_max->second).get_lambda()() : get_max_bound();
            }
        }

        std::string get_string(const T& t) const
        {
            std::stringstream ss;
            Serialize v(ss);
            t->accept(v);
            return ss.str();
        }

        bool bounds_already_set(const T& t) const
        {
            bool already_present = false;
            for (auto it = min.begin() ; (it != min.end()) && (not(already_present)) ; ++it)
            {
                if (it->first == get_string(t)) already_present = true;
            }
            for (auto it = max.begin() ; (it != max.end()) && (not(already_present)) ; ++it)
            {
                if (it->first == get_string(t)) already_present = true;
            }
            return already_present;
        }

        bool has(const T& t) const
        {
            bool already_present = false;
            for (auto it = val.begin() ; (it != val.end()) && (not(already_present)) ; ++it)
            {
                if (get_string(*it) == get_string(t)) already_present = true;
            }
            return already_present;
        }

        std::vector<std::function<double()> > get() const
        {
            std::vector<std::function<double()> > ret;
            for (auto it = val.begin() ; it != val.end() ; ++it)
            {
                ret.push_back((*it)->get_lambda());
            }
            return ret;
        }

        void clear_bounds()
        {
            min.clear();
            max.clear();
        }

    private:
        std::map<std::string,Parameter> min;
        std::map<std::string,Parameter> max;
        std::vector<T> val;
};

template <> void MinMaxList<StatePtr>::add_to_val(const StatePtr& v)
{
    append(val, v);
}

class OptimizationProblem::OptimizationProblem_pimpl
{
    public:
        OptimizationProblem_pimpl() : objective_function(Null().clone()),
                                      constraints(MinMaxList<NodePtr>()),
                                      states(MinMaxList<StatePtr>()),
                                      sigma_f(Parameter(2)),
                                      lambda(std::vector<Parameter>())
        {

        }

        std::vector<NodePtr> get_constraints() const
        {
            return constraints.get_vals();
        }

        StateList get_states() const
        {
            return states.get_vals();
        }

        void register_states()
        {
            auto s = ::get_states(objective_function, constraints.get_vals());
            for (auto it = s.begin() ; it != s.end() ; ++it)
            {
                states.add_to_val(*it);
            }
        }

        void reset_state_bounds()
        {
            states.clear_bounds();
        }

        NodePtr objective_function;
        MinMaxList<NodePtr> constraints;
        MinMaxList<StatePtr> states;
        Parameter sigma_f;
        std::vector<Parameter> lambda;
};

OptimizationProblem::OptimizationProblem() : pimpl(new OptimizationProblem_pimpl())
{
}

OptimizationProblem::~OptimizationProblem()
{

}

OptimizationProblem& OptimizationProblem::minimize(const NodePtr& objective_function)
{
    pimpl->objective_function = objective_function;
    pimpl->register_states();
    return *this;
}

OptimizationProblem& OptimizationProblem::subject_to(const Parameter& min_bound, const NodePtr& constraint)
{
    pimpl->constraints.push_back(min_bound, constraint);
    pimpl->register_states();
    pimpl->lambda.push_back(Parameter(11));
    return *this;
}

OptimizationProblem& OptimizationProblem::subject_to(const Parameter& min_bound, const NodePtr& constraint, const Parameter& max_bound)
{
    pimpl->constraints.push_back(min_bound,constraint,max_bound);
    pimpl->register_states();
    pimpl->lambda.push_back(Parameter(12));
    return *this;
}

OptimizationProblem& OptimizationProblem::subject_to(const NodePtr& constraint, const Parameter& max_bound)
{
    pimpl->constraints.push_back(constraint,max_bound);
    pimpl->register_states();
    pimpl->lambda.push_back(Parameter(13));
    return *this;
}

OptimizationProblem& OptimizationProblem::bound_state(const Parameter& min_bound, const StatePtr& state, const Parameter& max_bound)
{
    if (not(pimpl->states.has(state)))
    {
        std::stringstream ss;
        ss << "State '" << state->get_name() << "' is not present in this optimization problem.";
        THROW(__PRETTY_FUNCTION__, OptimizationProblemException, ss.str());
    }
    if (pimpl->states.bounds_already_set(state))
    {
        THROW(__PRETTY_FUNCTION__, OptimizationProblemException, "Attempting to set bounds to the same state twice.");
    }
    pimpl->states.push_back(min_bound, state, max_bound);
    return *this;
}

OptimizationProblem& OptimizationProblem::bound_state(const StatePtr& state, const Parameter& max_bound)
{
    if (not(pimpl->states.has(state)))
    {
        std::stringstream ss;
        ss << "State '" << state->get_name() << "' is not present in this optimization problem.";
        THROW(__PRETTY_FUNCTION__, OptimizationProblemException, ss.str());
    }
    if (pimpl->states.bounds_already_set(state))
    {
        THROW(__PRETTY_FUNCTION__, OptimizationProblemException, "Attempting to set bounds to the same state twice.");
    }
    pimpl->states.push_back(state, Parameter(max_bound));
    return *this;
}
OptimizationProblem& OptimizationProblem::bound_state(const Parameter& min_bound, const StatePtr& state)
{
    if (not(pimpl->states.has(state)))
    {
        std::stringstream ss;
        ss << "State '" << state->get_name() << "' is not present in this optimization problem.";
        THROW(__PRETTY_FUNCTION__, OptimizationProblemException, ss.str());
    }
    if (pimpl->states.bounds_already_set(state))
    {
        THROW(__PRETTY_FUNCTION__, OptimizationProblemException, "Attempting to set bounds to the same state twice.");
    }
    pimpl->states.push_back(min_bound, state);
    return *this;
}

void OptimizationProblem::reset_state_bounds()
{
    pimpl->reset_state_bounds();
}

StateList OptimizationProblem::get_states() const
{
    return pimpl->states.get_vals();
}

std::function<double()> OptimizationProblem::get_objective_function() const
{
    return pimpl->objective_function->get_lambda();
}

std::vector<std::function<double()> > OptimizationProblem::get_constraints() const
{
    return pimpl->constraints.get();
}

Grad OptimizationProblem::get_grad_objective_function() const
{
    return grad(pimpl->objective_function, pimpl->get_states());
}

FunctionMatrix OptimizationProblem::get_constraint_jacobian() const
{
    return jac(pimpl->constraints.get_vals(), pimpl->get_states());
}

FunctionMatrix OptimizationProblem::get_hessian() const
{
    return hes(pimpl->objective_function,pimpl->constraints.get_vals(),pimpl->sigma_f,pimpl->lambda,pimpl->get_states());
}

Parameter OptimizationProblem::get_sigma_f() const
{
    return pimpl->sigma_f;
}

std::vector<Parameter> OptimizationProblem::get_lambda() const
{
    return pimpl->lambda;
}

void OptimizationProblem::get_constraint_bounds(const size_t& m, double* const gl, double* const gu) const
{
    pimpl->constraints.get_bounds(m, gl, gu);
}

void OptimizationProblem::get_state_bounds(const size_t& n, double* const xl, double* const xu) const
{
    pimpl->states.get_bounds(n, xl, xu);
}

#include "test_macros.hpp"
::std::ostream& operator<<(::std::ostream& os, const OptimizationProblem& pb)
{
    os << "min " << *(pb.pimpl->objective_function) << std::endl;
    auto l = pb.get_states();
    if (not(l.empty()))
    {
        os << "(";
    }
    const size_t n = l.size();
    for (size_t i = 0 ; i < ((n-1)>n?0:(n-1)) ; ++i)
    {
        os << *(l.at(i)) << ",";
    }
    if (not(l.empty()))
    {
        os << *(l.back());
        os << ")" << std::endl;
    }
    auto constraints = pb.pimpl->get_constraints();
    const size_t m = constraints.size();
    double *gu = new double[m];
    double *gl = new double[m];
    pb.get_constraint_bounds(m, gl, gu);
    for (size_t i = 0 ; i < m ; ++i)
    {
        os << "subject to ";
        os << gl[i] << " < " << *(constraints.at(i)) << " < " << gu[i] << std::endl;
    }
    delete[] gl;
    delete[] gu;
    double *xu = new double[l.size()];
    double *xl = new double[l.size()];
    pb.get_state_bounds(n, xl, xu);
    for (size_t i = 0 ; i < n ; ++i)
    {
        os << xl[i] << " < " << *(l.at(i)) << " < " << xu[i] << std::endl;
    }
    delete[] xl;
    delete[] xu;
    return os;
}
