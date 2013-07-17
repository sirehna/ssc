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
#include "test_macros.hpp"

#include <cstdlib>
extern "C"
{
//    #include "cquad.h"
void dqags_(double f(void*,double*), void*, double*, double*, double*, double*, double*, double*, int*, int*, int*, int*, int* last, int* iwork, double* work);
}

double quadpack_integrand(void* obj, double* x);


double quadpack_integrand(void* obj, double* x)
{
    QuadPack* qpi = (QuadPack*)(obj);
    const double ret = qpi->op(x);
    return ret;
}

QuadPack::QuadPack(const Function& f_) : Integrator(f_),
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

double QuadPack::op(double *x)
{
    const double ret = f(*x);
    return ret;
}

double QuadPack::integrate(double a, double b, double eps) const
{
    int neval = 0;
    int ier = 0;
    int last = 0;

    double epsabs = eps;
    double epsrel = 1E-4;
    double abserr = 1E-4;

    int lenw = LENW, limit = LIMIT;
    double res = 0;
    dqags_(quadpack_integrand, (void*)(this), &a, &b, &epsabs, &epsrel, &res, &abserr, &neval, &ier, &limit, &lenw, &last, iwork, work);
/*COUT(res);
COUT(lenw);
COUT(limit);
COUT(epsabs);
COUT(epsabs);
COUT(a);
COUT(b);
COUT(neval);
COUT(ier);*/
    return res;
}

QuadPack::~QuadPack()
{
    delete [] iwork;
    delete [] work;
}

QuadPack::QuadPack(const QuadPack& rhs) : Integrator(rhs.f),
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

QuadPack& QuadPack::operator=(const QuadPack& rhs)
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

