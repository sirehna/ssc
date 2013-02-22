/*
 * OptimizationProblem.cpp
 *
 * \date 21 févr. 2013, 10:15:54
 *  \author cec
 */

#include "OptimizationProblem.hpp"
#include "Parameter.hpp"
#include "Null.hpp"
#include <map>
#include "State.hpp"
#include "Serialize.hpp"

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
            (void)max_;
            max[get_string(val_)] = max_;
        }

        double get_max_bound() const
        {
            return 2e19;
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
                l[i]   = found_value_in_min_map ? *(it_min->second) : get_min_bound();
                u[i++] = found_value_in_max_map ? *(it_max->second) : get_max_bound();
            }
        }

        std::string get_string(const T& t) const
        {
            std::stringstream ss;
            Serialize v(ss);
            t->accept(v);
            return ss.str();
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
                                      states(MinMaxList<StatePtr>())
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

        NodePtr objective_function;
        MinMaxList<NodePtr> constraints;
        MinMaxList<StatePtr> states;
};

OptimizationProblem::OptimizationProblem() : pimpl(new OptimizationProblem_pimpl())
{
}

OptimizationProblem& OptimizationProblem::minimize(const NodePtr& objective_function)
{
    pimpl->objective_function = objective_function;
    pimpl->register_states();
    return *this;
}

OptimizationProblem& OptimizationProblem::subject_to(const double& min_bound, const NodePtr& constraint)
{
    pimpl->constraints.push_back(min_bound, constraint);
    pimpl->register_states();
    return *this;
}

OptimizationProblem& OptimizationProblem::subject_to(const double& min_bound, const NodePtr& constraint, const double& max_bound)
{
    pimpl->constraints.push_back(min_bound,constraint,max_bound);
    pimpl->register_states();
    return *this;
}

OptimizationProblem& OptimizationProblem::bound_state(const double& min_bound, const StatePtr& state, const double& max_bound)
{
    pimpl->states.push_back(min_bound, state, max_bound);
    return *this;
}

OptimizationProblem& OptimizationProblem::bound_state(const StatePtr& state, const double& max_bound)
{
    pimpl->states.push_back(state, Parameter(max_bound));
    return *this;
}
OptimizationProblem& OptimizationProblem::bound_state(const double& min_bound, const StatePtr& state)
{
    pimpl->states.push_back(min_bound, state);
    return *this;
}

StateList OptimizationProblem::get_states() const
{
    return pimpl->states.get_vals();
}

NodePtr OptimizationProblem::get_objective_function() const
{
    return pimpl->objective_function;
}

void OptimizationProblem::get_constraint_bounds(const size_t& n, double* const gl, double* const gu) const
{
    pimpl->constraints.get_bounds(n, gl, gu);
}

void OptimizationProblem::get_state_bounds(const size_t& n, double* const xl, double* const xu) const
{
    pimpl->states.get_bounds(n, xl, xu);
}
