/*
 * Simpson.cpp
 *
 * \date 23 avr. 2013, 15:39:50
 *  \author cec
 */

#include "Simpson.hpp"
#include "test_macros.hpp"
#include <cmath>

class Simpson::Impl
{
    public:
        Impl(const Function& f_) : f(f_)
        {

        }
        double adaptive_simpson(const double& a, const double& b, const double& epsilon,
                const double& S, const double& fa, const double& fb, const double& fc, const int& bottom) const
        {
          const double c = (a + b)/2.;
          const double h = b - a;
          const double d = (a + c)/2.;
          const double e = (c + b)/2.;
          const double fd = f(d);
          const double fe = f(e);
          const double Sleft = (h/12)*(fa + 4*fd + fc);
          const double Sright = (h/12)*(fc + 4*fe + fb);
          const double S2 = Sleft + Sright;
          //COUT(bottom);
          if (bottom <= 0 || fabs(S2 - S) <= 15*epsilon)
            return S2 + (S2 - S)/15;
          return adaptive_simpson(a, c, epsilon/2., Sleft,  fa, fc, fd, bottom-1) +
                 adaptive_simpson(c, b, epsilon/2., Sright, fc, fb, fe, bottom-1);
        }

        double integrate(const double& a, const double& b, const double& eps) const
        {
            COUT(a);
            COUT(b);
            COUT(eps);
            const double c = (a + b)/2, h = b - a;
            const double fa = f(a), fb = f(b), fc = f(c);
            const double S = (h/6.)*(fa + 4*fc + fb);
            return adaptive_simpson(a, b, eps, S, fa, fb, fc, 20);
        }


    private:
        Function f;
};

Simpson::Simpson(const Function& f) : pimpl(new Impl(f))
{

}

double Simpson::integrate(const double& a, const double& b, const double& eps) const
{
    return pimpl->integrate(a,b,eps);
}
