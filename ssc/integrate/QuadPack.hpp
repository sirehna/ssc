/*
 * QuadPack.hpp
 *
 *  Created on: Dec 9, 2014
 *      Author: cady
 */

#ifndef QUADPACK_HPP_
#define QUADPACK_HPP_

#include "ssc/integrate/Integrator.hpp"

/** \author cec
 *  \ingroup integrate
 *  \brief Responsibility
 *  \details
 *  \section ex1 Example
 *  \snippet integrate/unit_tests/src/QuadPackTest.cpp QuadPackTest example
 *  \section ex2 Expected output
 *  \snippet integrate/unit_tests/src/QuadPackTest.cpp QuadPackTest expected output
 */
namespace ssc
{
    namespace integrate
    {
        class QuadPack : public Integrator
        {
            public:
                QuadPack();
                QuadPack(const Function& f_);
                virtual ~QuadPack();
                virtual double op(double *x) = 0;

            private:
                virtual double integrate_impl(const Function& f, double a, double b, double eps=1e-6) const = 0;

            protected:
                void throw_any_errors(const int error_code) const;
        };
    }
}

#endif /* QUADPACK_HPP_ */
