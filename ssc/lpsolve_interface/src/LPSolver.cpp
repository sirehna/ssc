/*
 * LPSolver.cpp
 *
 * \date 20 nov. 2013, 14:01:21
 *  \author cec
 */

#include "LPSolver.hpp"
#include "OptimizationProblem.hpp"
#include "lp_lib.h"
#include "LPSolverException.hpp"
#include "FunctionMatrix.hpp"
#include "State.hpp"

class LPSolver::Impl
{
    public:
        Impl() : pb(new OptimizationProblem()), nb_ob_states(0), nb_of_constraints(0), colno(NULL), row(NULL), lp(NULL)
        {

        }

        Impl(const Impl& rhs) : pb(new OptimizationProblem(*rhs.pb)),
                                nb_ob_states(pb->get_states().size()),
                                nb_of_constraints(pb->get_constraints().size()),
                                colno(new int[nb_ob_states]),
                                row(new REAL[nb_ob_states]),
                                lp(make_lp(0, nb_ob_states))
        {

        }

        Impl& operator=(const Impl& rhs)
        {
            if (&rhs != this)
            {
                pb = std::shared_ptr<OptimizationProblem>(new OptimizationProblem(*rhs.pb));
                nb_ob_states = pb->get_states().size();
                nb_of_constraints = pb->get_constraints().size();
                if (lp) delete_lp(lp);
                if (colno) delete[] colno;
                if (row) delete[] row;
                colno = new int[nb_ob_states];
                row = new REAL[nb_ob_states];
                lp = make_lp(0, nb_ob_states);
            }
            return *this;
        }

        ~Impl()
        {
            if (lp) delete_lp(lp);
            if (colno) delete[] colno;
            if (row) delete[] row;
        }
        Impl(const std::shared_ptr<OptimizationProblem>& problem) : pb(problem),
                                                                    nb_ob_states(pb->get_states().size()),
                                                                    nb_of_constraints(pb->get_constraints().size()),
                                                                    colno(new int[nb_ob_states]),
                                                                    row(new REAL[nb_ob_states]),
                                                                    lp(make_lp(0, nb_ob_states))
        {
        }

        OptimizationResult solve()
        {
            set_state_names(pb->get_states());
            add_constraints();
            return OptimizationResult();
        }

        void set_state_names(const std::vector<StatePtr>& states)
        {
            size_t i = 1;
            for (auto it = states.begin() ; it != states.end() ; ++it)
            {
                char* c = new char[(*it)->get_name().length()];
                strcpy(c, (*it)->get_name().c_str());
                set_col_name(lp, i++, c);
                delete[]c;
            }
        }

        void add_constraints()
        {
            std::vector<double> gl(nb_of_constraints), gu(nb_of_constraints);
            pb->get_constraint_bounds(nb_of_constraints, &gl[0], &gu[0]);
            const FunctionMatrix M = pb->get_constraint_jacobian();
            set_add_rowmode(lp, TRUE);
            const size_t n = M.values.size();
            size_t k = 0;
            for (size_t i = 0 ; i < nb_of_constraints ; ++i)
            {
                size_t p = 0;
                for (size_t j = 0 ; j < nb_ob_states ; ++j)
                {
                    if ((k < n) && (M.row_index[k] == i) && (M.col_index[k] == j))
                    {
                        colno[p] = M.col_index[k]+1;
                        row[p++] = M.values[k]();
                    }
                }
                add_constraintex(lp, p, row, colno, LE, gu[i]);
            }
        }

    private:
        std::shared_ptr<OptimizationProblem> pb;
        size_t nb_ob_states;
        size_t nb_of_constraints;
        int *colno;
        REAL *row;
        lprec* lp;
};

LPSolver::LPSolver(const std::shared_ptr<OptimizationProblem>& problem) : pimpl(new Impl(problem))
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

OptimizationResult LPSolver::solve()
{
    return pimpl->solve();
}
