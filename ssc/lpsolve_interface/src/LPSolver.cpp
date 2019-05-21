/*
 * LPSolver.cpp
 *
 * \date 20 nov. 2013, 14:01:21
 * \author cec
 */

#include "LPSolver.hpp"
#include "OptimizationProblem.hpp"
#include "lp_lib.h"
#include "LPSolverException.hpp"
#include "FunctionMatrix.hpp"
#include "State.hpp"
#include "Grad.hpp"
#include "test_macros.hpp"
class LPSolver::Impl
{
    public:
        Impl() : pb(new OptimizationProblem()), nb_ob_states(0), nb_of_constraints(0), colno(NULL), row(NULL), lp(NULL), par(LPSolverParameters())
        {

        }

        Impl(const Impl& rhs) : pb(new OptimizationProblem(*rhs.pb)),
                                nb_ob_states(pb->get_states().size()),
                                nb_of_constraints(pb->get_constraints().size()),
                                colno(new int[nb_ob_states]),
                                row(new double[nb_ob_states]), lp(
                        make_lp(0, nb_ob_states)),
                        par(rhs.par)
        {
        }

        Impl& operator =(const Impl& rhs)
        {
            if (&rhs != this)
            {
                pb = std::tr1::shared_ptr < OptimizationProblem
                        > (new OptimizationProblem(*rhs.pb));
                nb_ob_states = pb->get_states().size();
                nb_of_constraints = pb->get_constraints().size();
                if (lp)
                    delete_lp(lp);
                if (colno)
                    delete[] colno;
                if (row)
                    delete[] row;
                colno = new int[nb_ob_states];
                row = new REAL[nb_ob_states];
                lp = make_lp(0, nb_ob_states);
                par = rhs.par;
            }
            return *this;
        }

        ~Impl()
        {
            if (lp)
                delete_lp(lp);

            if (colno)
                delete[] colno;

            if (row)
                delete[] row;
        }
        Impl(const std::tr1::shared_ptr<OptimizationProblem>& problem, const LPSolverParameters& par_) :
                pb(problem), nb_ob_states(pb->get_states().size()), nb_of_constraints(
                        pb->get_constraints().size()), colno(
                        new int[nb_ob_states]), row(new double[nb_ob_states]), lp(
                        make_lp(0, nb_ob_states)),
                        par(par_)
        {
        }

        StateList initialize_states(const std::vector<double>& x0)
        {
            const auto states = pb->get_states();
            for (size_t i = 0; i < nb_ob_states; ++i)
            {
                *states.at(i) = x0.at(i);
            }
            return states;
        }

        OptimizationResult get_result()
        {
            set_verbose(lp, par.verbose_level);
            const int ierr = ::solve(lp);
            OptimizationResult res;
            res.converged = (ierr == OPTIMAL);
            get_variables(lp, row);
            for (size_t i = 0; i < nb_ob_states; ++i)
            {
                res.state_values[get_col_name(lp, i + 1)] = row[i];
            }
            res.nb_of_iterations = get_total_iter(lp);
            res.value_of_the_objective_function = get_objective(lp);
            res.total_time_needed_for_optimization = time_elapsed(lp);
            return res;
        }

        void set_binary_and_integer_states()
        {
            const auto idx_bin = pb->get_index_of_binary_variables();
            const auto idx_int = pb->get_index_of_binary_variables();
            for (auto it = idx_bin.begin() ; it != idx_bin.end() ; ++it)
            {
                set_binary(lp, *it+1, TRUE);
            }
            for (auto it = idx_int.begin() ; it != idx_int.end() ; ++it)
            {
                set_int(lp, *it+1, TRUE);
            }
        }

        OptimizationResult solve(const std::vector<double>& x0)
        {
            const auto states = initialize_states(x0);
            set_state_names(states);
            set_binary_and_integer_states();
            if (nb_of_constraints) set_constraints();
            set_objective_function();
            return get_result();
        }

        void set_state_names(const std::vector<StatePtr>& states)
        {
            size_t i = 1;
            for (auto it = states.begin(); it != states.end(); ++it)
            {
                const std::string str = (*it)->get_name();
                char * writable = new char[str.size() + 1];
                std::copy(str.begin(), str.end(), writable);
                writable[str.size()] = '\0';
                set_col_name(lp, i++, writable);
                delete[] writable;
            }
        }

        void set_objective_function()
        {
            const Grad grad_f = pb->get_grad_objective_function();
            const size_t n = grad_f.index.size();
            for (size_t k = 0; k < n; ++k)
            {
                colno[k] = grad_f.index.at(k) + 1;
                row[k] = grad_f.values.at(k)();
            }
            set_obj_fnex(lp, n, row, colno);
            if (!(pb->is_a_minimization_problem()))
                set_maxim(lp);
        }
        void set_constraints()
        {
            std::vector<double> gl(nb_of_constraints), gu(nb_of_constraints);
            pb->get_constraint_bounds(nb_of_constraints, &gl[0], &gu[0]);
            const FunctionMatrix M = pb->get_constraint_jacobian();
            set_add_rowmode(lp, TRUE);
            const size_t n = M.values.size();
            int previous_row = -1;
            size_t p = 0;
            for (size_t k = 0; k < n; ++k)
            {
                const auto i = (int) M.row_index[k];
                const auto j = (int) M.col_index[k];
                if (i != previous_row)
                {
                    if (previous_row > -1)
                    {
                        add_constraintex(lp, p, row, colno, LE,
                                gu[previous_row]);
                    }
                    p = 0;
                }
                colno[p] = j + 1;
                row[p++] = M.values[k]();
                previous_row = i;
            }
            if (p)
                add_constraintex(lp, p, row, colno, LE, gu[M.row_index[n - 1]]);

            set_add_rowmode(lp, FALSE);
        }

    private:
        std::tr1::shared_ptr<OptimizationProblem> pb;
        size_t nb_ob_states;
        size_t nb_of_constraints;
        int* colno;
        double*row;
        lprec* lp;
        LPSolverParameters par;
};

LPSolver::LPSolver(const std::tr1::shared_ptr<OptimizationProblem>& problem, const LPSolverParameters& par) : pimpl(new Impl(problem,par))
{

}

LPSolver::LPSolver() : pimpl(new Impl())
{

}

LPSolver::~LPSolver()
{

}

LPSolver::LPSolver(const LPSolver& rhs) : pimpl(new Impl(*rhs.pimpl))
{

}

LPSolver& LPSolver::operator=(const LPSolver& rhs)
{
    if (&rhs != this)
    {
        pimpl = std::unique_ptr<Impl>(new Impl(*rhs.pimpl));
    }
    return *this;
}

OptimizationResult LPSolver::solve(const std::vector<double>& x0)
{
    return pimpl->solve(x0);
}
