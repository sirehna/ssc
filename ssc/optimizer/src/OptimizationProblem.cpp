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
#include "SerializeReversePolish.hpp"
#include "GradHes.hpp"
#include "Grad.hpp"
#include "FunctionMatrix.hpp"

template <class T> std::string get_string(const T& t)
{
    std::stringstream ss;
    Serialize v(ss);
    t->accept(v);
    return ss.str();
}
template <> std::string get_string(const StatePtr& t);
template <> std::string get_string(const StatePtr& t)
{
    return t->get_name();
}

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
                THROW(__PRETTY_FUNCTION__, OptimizationProblemException, "Attempting to specify bounds for the same constraint twice");
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
                THROW(__PRETTY_FUNCTION__, OptimizationProblemException, "l == NULL");
            }
            if (u == NULL)
            {
                THROW(__PRETTY_FUNCTION__, OptimizationProblemException, "u == NULL");
            }
            if (n!= val.size())
            {
                THROW(__PRETTY_FUNCTION__, OptimizationProblemException, "Invalid size");
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

enum class VariableType {CONTINUOUS, INTEGER, BINARY};

class OptimizationProblem::OptimizationProblem_pimpl
{
    public:
        OptimizationProblem_pimpl() : objective_function(Null().clone()),
                                      constraints(MinMaxList<NodePtr>()),
                                      states(MinMaxList<StatePtr>()),
                                      sigma_f(Parameter(2)),
                                      lambda(std::vector<Parameter>()),
                                      minimize(false),
                                      variable_types(std::map<std::string,VariableType>()),
                                      index(std::map<std::string,size_t>()),
                                      binary_var_idx(std::vector<size_t>()),
                                      integer_var_idx(std::vector<size_t>())
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
            size_t k = 0;
            for (auto it = s.begin() ; it != s.end() ; ++it)
            {
                states.add_to_val(*it);
                variable_types[(*it)->get_name()] = VariableType::CONTINUOUS;
                index[(*it)->get_name()] = k++;
            }
        }

        void binary(const StatePtr& state)
        {
            if (states.bounds_already_set(state))
            {
                std::stringstream ss;
                ss << "Bounds for state '" << state->get_name() << "' were already set"
                   << ", therefore it is considered continuous. It cannot now be declared binary.";
                THROW(__PRETTY_FUNCTION__, OptimizationProblemException, ss.str());
            }
            if (variable_types[state->get_name()] == VariableType::BINARY)
            {
                std::stringstream ss;
                ss << "State '" << state->get_name() << "' was already declared binary: don't declare it twice.";
                THROW(__PRETTY_FUNCTION__, OptimizationProblemException, ss.str());
            }
            if (variable_types[state->get_name()] == VariableType::INTEGER)
            {
                std::stringstream ss;
                ss << "State '" << state->get_name() << "' was declared integer. It cannot now be declare binary.";
                THROW(__PRETTY_FUNCTION__, OptimizationProblemException, ss.str());
            }
            variable_types[state->get_name()] = VariableType::BINARY;
            binary_var_idx.push_back(index[state->get_name()]);
        }

        void integer(const StatePtr& state)
        {
            if (states.bounds_already_set(state))
            {
                std::stringstream ss;
                ss << "Bounds for state '" << state->get_name() << "' were already set"
                   << ", therefore it is considered continuous. It cannot now be declared integer.";
                THROW(__PRETTY_FUNCTION__, OptimizationProblemException, ss.str());
            }
            if (variable_types[state->get_name()] == VariableType::INTEGER)
            {
                std::stringstream ss;
                ss << "State '" << state->get_name() << "' was already declared integer: don't declare it twice.";
                THROW(__PRETTY_FUNCTION__, OptimizationProblemException, ss.str());
            }
            if (variable_types[state->get_name()] == VariableType::BINARY)
            {
                std::stringstream ss;
                ss << "State '" << state->get_name() << "' was declared binary. It cannot now be declare integer.";
                THROW(__PRETTY_FUNCTION__, OptimizationProblemException, ss.str());
            }
            variable_types[state->get_name()] = VariableType::INTEGER;
            integer_var_idx.push_back(index[state->get_name()]);
        }

        bool do_we_have(const VariableType& v) const
        {
            for (auto it = variable_types.begin() ; it != variable_types.end() ; ++it)
            {
                if (it->second == v) return true;
            }
            return false;
        }

        void reset_state_bounds()
        {
            states.clear_bounds();
        }

        std::vector<size_t> get_binary_variables() const
        {
            return binary_var_idx;
        }

        std::vector<size_t> get_integer_variables() const
        {
            return integer_var_idx;
        }

        NodePtr objective_function;
        MinMaxList<NodePtr> constraints;
        MinMaxList<StatePtr> states;
        Parameter sigma_f;
        std::vector<Parameter> lambda;
        bool minimize;
        std::map<std::string,VariableType> variable_types;
        std::map<std::string,size_t> index;
        std::vector<size_t> binary_var_idx;
        std::vector<size_t> integer_var_idx;
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
    pimpl->minimize = true;
    return *this;
}

OptimizationProblem& OptimizationProblem::maximize(const NodePtr& objective_function)
{
    pimpl->objective_function = objective_function;
    pimpl->register_states();
    pimpl->minimize = false;
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

void OptimizationProblem::check_state_for_bound_setting(const StatePtr& state) const
{
    if (pimpl->variable_types[state->get_name()] != VariableType::CONTINUOUS)
    {
        std::stringstream ss;
        ss << "State '" << state->get_name() << "' is not continuous (it was declared ";
        switch(pimpl->variable_types[state->get_name()])
        {
            case VariableType::CONTINUOUS:
                ss << "continuous";
                break;
            case VariableType::INTEGER:
                ss << "integer";
                break;
            case VariableType::BINARY:
                ss << "binary";
                break;
        }
        ss << ")";
        THROW(__PRETTY_FUNCTION__, OptimizationProblemException, ss.str());
    }
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
}

OptimizationProblem& OptimizationProblem::bound_state(const Parameter& min_bound, const StatePtr& state, const Parameter& max_bound)
{
    check_state_for_bound_setting(state);
    pimpl->states.push_back(min_bound, state, max_bound);
    return *this;
}

OptimizationProblem& OptimizationProblem::bound_state(const StatePtr& state, const Parameter& max_bound)
{
    check_state_for_bound_setting(state);
    pimpl->states.push_back(state, Parameter(max_bound));
    return *this;
}
OptimizationProblem& OptimizationProblem::bound_state(const Parameter& min_bound, const StatePtr& state)
{
    check_state_for_bound_setting(state);
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

::std::ostream& operator<<(::std::ostream& os, const OptimizationProblem& pb)
{
    SerializeReversePolish s(os);
    if (pb.is_a_minimization_problem())
    {
        os << "min ";
    }
    else
    {
        os << "max ";
    }
    pb.pimpl->objective_function->accept(s);
    os << std::endl;

    auto l = pb.get_states();
    if (not(l.empty()))
    {
        os << "(";
    }
    const size_t n = l.size();
    for (size_t i = 0 ; i < ((n-1)>n?0:(n-1)) ; ++i)
    {
        const auto x = l.at(i)/l.at(i)->get_multiplicative_factor();
        os << *(x);
        os << ",";

    }
    if (not(l.empty()))
    {
        const auto x = l.back()/l.back()->get_multiplicative_factor();
        os << *(x);
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
        os << gl[i] << " < ";
        constraints.at(i)->accept(s);
        os << " < " << gu[i] << std::endl;
    }
    delete[] gl;
    delete[] gu;
    double *xu = new double[l.size()];
    double *xl = new double[l.size()];
    pb.get_state_bounds(n, xl, xu);
    for (size_t i = 0 ; i < n ; ++i)
    {
        const auto x = l.back()/l.back()->get_multiplicative_factor();
        os << xl[i] << " < " << *(x) << " < " << xu[i] << std::endl;
    }
    delete[] xl;
    delete[] xu;
    return os;
}

bool OptimizationProblem::is_a_minimization_problem() const
{
    return pimpl->minimize;
}

bool OptimizationProblem::has_binary_variables() const
{
    return pimpl->do_we_have(VariableType::BINARY);
}

bool OptimizationProblem::has_integer_variables() const
{
    return pimpl->do_we_have(VariableType::INTEGER);
}

bool OptimizationProblem::has_continuous_variables() const
{
    return pimpl->do_we_have(VariableType::CONTINUOUS);
}

OptimizationProblem& OptimizationProblem::binary(const StatePtr& state)
{
    pimpl->binary(state);
    return *this;
}

OptimizationProblem& OptimizationProblem::integer(const StatePtr& state)
{
    pimpl->integer(state);
    return *this;
}

std::vector<size_t> OptimizationProblem::get_index_of_binary_variables() const
{
    return pimpl->get_binary_variables();
}

std::vector<size_t> OptimizationProblem::get_index_of_integer_variables() const
{
    return pimpl->get_integer_variables();
}
