/*
 * QuadPack.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: cady
 */

#include <sstream>

#include <ssc/integrate/QuadPack.hpp>

#include "ssc/exception_handling/Exception.hpp"
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

ssc::integrate::QuadPack::QuadPack(const Function& f_) : Integrator(f_)
{
}

ssc::integrate::QuadPack::QuadPack() : Integrator()
{
}

ssc::integrate::QuadPack::~QuadPack()
{
}

double ssc::integrate::QuadPack::op(double *x)
{
    const double ret = f(*x);
    return ret;
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
        ss << "Maximum number of subdivisions allowed has been achieved. One can allow more sub-divisions by increasing the value of limit (and taking the according dimension adjustments into account). However, if this yields no improvement it is advised to analyze the integrand in order to determine the integration difficulties. If the position of a local difficulty can be determined (e.g. singularity, discontinuity within the interval) one will probably gain from splitting up the interval at this point and calling the integrator on the subranges. If possible, an appropriate special-purpose integrator should be used, which is designed for handling the type of difficulty involved.";
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
