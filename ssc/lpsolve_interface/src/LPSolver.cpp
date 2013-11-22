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

class LPSolver::Impl
{
    public:
        Impl() : pb(new OptimizationProblem()), Ncol(0), colno(NULL), row(NULL), lp(NULL)
        {

        }

        Impl(const Impl& rhs) : pb(new OptimizationProblem(*rhs.pb)),
                                Ncol(pb->get_states().size()),
                                colno(new int[Ncol]),
                                row(new REAL[Ncol]),
                                lp(make_lp(0, Ncol))
        {

        }

        Impl& operator=(const Impl& rhs)
        {
            if (&rhs != this)
            {
                pb = std::shared_ptr<OptimizationProblem>(new OptimizationProblem(*rhs.pb));
                Ncol = pb->get_states().size();
                if (lp) delete_lp(lp);
                if (colno) delete[] colno;
                if (row) delete[] row;
                colno = new int[Ncol];
                row = new REAL[Ncol];
                lp = make_lp(0, Ncol);
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
                                                                    Ncol(pb->get_states().size()),
                                                                    colno(new int[Ncol]),
                                                                    row(new REAL[Ncol]),
                                                                    lp(make_lp(0, Ncol))
        {
        }

        OptimizationResult solve()
        {
            return OptimizationResult();
        }

    private:
        std::shared_ptr<OptimizationProblem> pb;
        int Ncol;
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
