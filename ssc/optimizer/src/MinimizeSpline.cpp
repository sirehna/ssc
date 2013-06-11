/*
 * MinimizeSpline.cpp
 *
 * \date 10 juin 2013, 11:48:50
 *  \author cec
 */

#include "MinimizeSpline.hpp"
#include "OptimizationProblem.hpp"
#include "State.hpp"
#include "SplineFunctor.hpp"
#include "IpoptSolver.hpp"
#include "OptimizationResult.hpp"
#include <algorithm>

class MinimizeSpline::Impl
{

    public:
        Impl(double xmin, double xmax, const std::vector<double>& y): x(new State("x",0)),
                                                                      f(x,xmin,xmax,y),
                                                                      problem(new OptimizationProblem()),
                                                                      solver(IpoptSolver()),
                                                                      x0(0)
        {
            problem->minimize(f.clone())
               .bound_state(xmin,x,xmax);
            solver = IpoptSolver(problem);
            const auto idx = std::min_element(y.begin(),y.end())-y.begin();
            x0 = xmin + (xmax-xmin)/(y.size()-1)*idx;

        }

        double get_min()
        {
            auto res = solver.solve(std::vector<double>(1,x0)).state_values;
            auto it = res.find(x->get_name());
            const double xopt = it->second;
            return xopt;
        }

    private:
        StatePtr x;
        SplineFunctor f;
        std::tr1::shared_ptr<OptimizationProblem> problem;
        IpoptSolver solver;
        double x0;
};


MinimizeSpline::MinimizeSpline(double xmin, double xmax, const std::vector<double>& y) : pimpl(new Impl(xmin,xmax,y))
{

}

/** \author cec
 *  \date 10 juin 2013, 13:13:16
 *  \brief Returns the position x0 of the minimum of the function interpolating y
 *  \snippet optimizer/unit_tests/src/MinimizeSplineTest.cpp MinimizeSplineTest MinimizeSpline::get_min_example
*/
double MinimizeSpline::get_min()
{
    return pimpl->get_min();
}
