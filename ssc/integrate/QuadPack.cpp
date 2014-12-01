/*
 * QuadPack.cpp
 *
 * \date 5 juil. 2013, 16:48:53
 *  \author cec
 */

#include "QuadPack.hpp"

#define LIMIT 250
#define LENW 1601
#define LENIW 500
#define MAXP1 21

#include "ssc/exception_handling/Exception.hpp"
#include <sstream>
#include <iostream>
#include <cassert>


namespace ssc
{
    namespace integrate
    {
        class QuadPackException : public ssc::exception_handling::Exception
        {
            public:
                QuadPackException(const char* s) : Exception(s)
                {
                }
        };
    }
}


#include <cstdlib>
extern "C"
{
void dqags_(double f(void*,double*), void*, double*, double*, double*, double*, double*, double*, int*, int*, int*, int*, int* last, int* iwork, double* work);
}

double quadpack_integrand(void* obj, double* x);


double quadpack_integrand(void* obj, double* x)
{
    ssc::integrate::QuadPack* qpi = (ssc::integrate::QuadPack*)(obj);
    const double ret = qpi->op(x);
    return ret;
}

ssc::integrate::QuadPack::QuadPack() : Integrator(),
                                       iwork(new int[LIMIT]),
                                       work(new double[LENW])
{
}

ssc::integrate::QuadPack::QuadPack(const Function& f_) : Integrator(f_),
                                         iwork(new int[LIMIT]),
                                         work(new double[LENW])
{
    for (size_t i = 0 ; i < LIMIT ; ++i)
    {
        iwork[i] = 0;
    }
    for (size_t i = 0 ; i < LENW ; ++i)
    {
        work[i] = 0;
    }
}

double ssc::integrate::QuadPack::op(double *x)
{
    const double ret = f(*x);
    return ret;
}

double ssc::integrate::QuadPack::integrate_impl(const Function& f_, double a, double b, double eps) const
{
    int neval = 0;
    int ier = 0;
    int last = 0;

    double epsabs = eps;
    double epsrel = 1E-4;
    double abserr = 1E-4;

    int lenw = LENW, limit = LIMIT;
    double res = 0;
    QuadPack q(f_);
    dqags_(quadpack_integrand, (void*)(&q), &a, &b, &epsabs, &epsrel, &res, &abserr, &neval, &ier, &limit, &lenw, &last, iwork, work);
    throw_any_errors(ier);
    return res;
}

void ssc::integrate::QuadPack::throw_any_errors(const int ier) const
{
    if (ier < 0)
    {
        std::stringstream ss;
        ss << "ier = " << ier << ": possible memory corruption";
        THROW(__PRETTY_FUNCTION__, ssc::integrate::QuadPackException, ss.str());
    }
    if (ier == 1)
    {
        std::stringstream ss;
        ss << "Maximum number of subdivisions allowed has been achieved. One can allow more sub-divisions by increasing the value of limit (and taking the according dimension adjustments into account. However, if this yields no improvement it is advised to analyze the integrand in order to determine the integration difficulties. If the position of a local difficulty can be determined (e.g. singularity, discontinuity within the interval) one will probably gain from splitting up the interval at this point and calling the integrator on the subranges. If possible, an appropriate special-purpose integrator should be used, which is designed for handling the type of difficulty involved.";
        THROW(__PRETTY_FUNCTION__, ssc::integrate::QuadPackException, ss.str());
    }
    if (ier == 2)
    {
        std::stringstream ss;
        ss << "The occurrence of roundoff error is detected, which prevents the requested tolerance from being achieved. The error may be under-estimated.";
        THROW(__PRETTY_FUNCTION__, ssc::integrate::QuadPackException, ss.str());
    }
    if (ier == 3)
    {
        std::stringstream ss;
        ss << "Extremely bad integrand behaviour occurs at some points of the integration interval.";
        THROW(__PRETTY_FUNCTION__, ssc::integrate::QuadPackException, ss.str());
    }
    if (ier == 4)
    {
        std::stringstream ss;
        ss << "The algorithm does not converge. Roundoff error is detected in the extrapolation table. It is presumed that the requested tolerance cannot be achieved, and that the returned result is the best which can be obtained.";
        THROW(__PRETTY_FUNCTION__, QuadPackException, ss.str());
    }
    if (ier == 5)
    {
        std::stringstream ss;
        ss << "The integral is probably divergent, or slowly convergent.";
        THROW(__PRETTY_FUNCTION__, ssc::integrate::QuadPackException, ss.str());
    }
    if (ier == 6)
    {
        std::stringstream ss;
        ss << "The input is invalid, because (epsabs<=0 and epsrel<max(50*rel.mach.acc.,0.5d-28) or limit<1 or lenw<limit*4.";
        THROW(__PRETTY_FUNCTION__, ssc::integrate::QuadPackException, ss.str());
    }
}

ssc::integrate::QuadPack::~QuadPack()
{
    if (iwork) delete [] iwork;
    if (work)  delete [] work;
}

ssc::integrate::QuadPack::QuadPack(const QuadPack& rhs) : Integrator(rhs.f),
                                          iwork(new int[LIMIT]),
                                          work(new double[LENW])
{
    for (size_t i = 0 ; i < LIMIT ; ++i)
    {
        iwork[i] = rhs.iwork[i];
    }
    for (size_t i = 0 ; i < LENW ; ++i)
    {
        work[i] = rhs.work[i];
    }
}

ssc::integrate::QuadPack& ssc::integrate::QuadPack::operator=(const QuadPack& rhs)
{
    if (this != &rhs)
    {
        delete iwork;
        delete work;
        iwork = new int[LIMIT];
        work = new double[LENW];
        for (size_t i = 0 ; i < LIMIT ; ++i)
        {
            iwork[i] = rhs.iwork[i];
        }
        for (size_t i = 0 ; i < LENW ; ++i)
        {
            work[i] = rhs.work[i];
        }
    }
    return *this;
}

