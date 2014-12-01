/*
 * QuadPack.hpp
 *
 * \date 5 juil. 2013, 16:48:53
 *  \author cec
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
                ~QuadPack();
                QuadPack(const QuadPack& rhs);
                QuadPack& operator=(const QuadPack& rhs);
                double op(double *x);

            private:
                double integrate_impl(const Function& f, double a, double b, double eps=1e-6) const;
                void throw_any_errors(const int error_code) const;
                int* iwork;
                double* work;
        };
    }
}

#endif /* QUADPACK_HPP_ */
