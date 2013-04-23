/*
 * TrapezoidalIntegration.cpp
 *
 * \date 23 avr. 2013, 14:47:22
 *  \author cec
 */

#include "TrapezoidalIntegration.hpp"

class TrapezoidalIntegration::Impl
{
    public:
        Impl(const Function& f_) : f(f_)
        {

        }

        double integrate(const double& a, const double& b, const size_t& nb_of_evaluations) const
        {
            const double h = (b - a) / nb_of_evaluations;
            double S = f(a) + f(b);
            for (size_t i  = 1 ; i < nb_of_evaluations ; ++i)
            {
                S += 2 * f(a + i * h);
            }
            return S * h / 2.;
        }


    private:
        Function f;
};



TrapezoidalIntegration::TrapezoidalIntegration(const Function& f) : pimpl(new Impl(f))
{

}


double TrapezoidalIntegration::integrate(const double& a, const double& b, const size_t& nb_of_evaluations) const
{
    return pimpl->integrate(a,b,nb_of_evaluations);
}
