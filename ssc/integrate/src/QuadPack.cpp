/*
 * QuadPack.cpp
 *
 * \date 5 juil. 2013, 16:48:53
 *  \author cec
 */

#include "QuadPack.hpp"

#include <cstdlib>
extern "C"
{
    #include "cquad.h"
}

double quadpack_integrand(void* obj, double* x);


double quadpack_integrand(void* obj, double* x)
{
    QuadPack* qpi = (QuadPack*)obj;
    return qpi->op(x);
}

QuadPack::QuadPack(const Function& f_) : Integrator(f_){}

double QuadPack::op(double *x)
{
    return f(*x);
}

double QuadPack::integrate(const double& a, const double& b, const double& eps) const
{
    double epsabs, result, abserr, *work;
    int neval, ier, last, *iwork;

    epsabs = 0;

 // allocate memory
    iwork = (int *) calloc(LIMIT, sizeof(int));
    work = (double *) calloc(LENW, sizeof(double));

    result = cquad_dqags(quadpack_integrand, (void*)this, a, b, epsabs, eps, &abserr, &neval, &ier, &last, iwork, work);
    free(iwork);
    free(work);
    return result;
}
