/*
 * QuadPack.hpp
 *
 * \date 5 juil. 2013, 16:48:53
 *  \author cec
 */

#ifndef QUADPACK_HPP_
#define QUADPACK_HPP_

#include "Integrator.hpp"

/** \author cec
 *  \ingroup integrate
 *  \brief Responsibility
 *  \details 
 *  \section ex1 Example
 *  \snippet integrate/unit_tests/src/QuadPackTest.cpp QuadPackTest example
 *  \section ex2 Expected output
 *  \snippet integrate/unit_tests/src/QuadPackTest.cpp QuadPackTest expected output
 */

class QuadPack : public Integrator
{
    public:
        QuadPack(const Function& f_);
        double op(double *x);
        double integrate(const double& a, const double& b, const double& eps=1e-6) const;
};


#endif /* QUADPACK_HPP_ */
