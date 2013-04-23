/*
 * Integrate.hpp
 *
 * \date 23 avr. 2013, 09:47:14
 *  \author cec
 */

#ifndef INTEGRATE_HPP_
#define INTEGRATE_HPP_

#include <functional>
#include <tr1/memory>

typedef std::function<double (const double&)> Function;

#include "Exception.hpp"

class IntegrateException : public Exception
{
    public:
        IntegrateException(const char* s) :
                Exception(s)
        {
        }
};


/** \author cec
 *  \brief Calculates an approximation result to a given definite integral  i = integral of f over (a,b)
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet quadpack/unit_tests/src/IntegrateTest.cpp IntegrateTest example
 *  \section ex2 Expected output
 *  \snippet quadpack/unit_tests/src/IntegrateTest.cpp IntegrateTest expected output
 */

class Integrate
{
    public:
        Integrate(const Function& f);
        double integrate(const double& a, const double& b) const;

    private:
        class IntegrateImpl;
        std::tr1::shared_ptr<IntegrateImpl> pimpl;
};

#endif /* INTEGRATE_HPP_ */
