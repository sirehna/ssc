/*
 * Integrator.hpp
 *
 * \date 5 juin 2013, 16:07:13
 *  \author cec
 */

#ifndef INTEGRATOR_HPP_
#define INTEGRATOR_HPP_
#include <functional>

typedef std::function<double (const double&)> Function;
/** \author cec
 *  \ingroup MODULE_NAME
 *  \brief Responsibility
 *  \details 
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/IntegratorTest.cpp IntegratorTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/IntegratorTest.cpp IntegratorTest expected output
 */
namespace ssc
{
    namespace integrate
    {
        class Integrator
        {
            public:
                Integrator(const Function& f_);
                virtual ~Integrator();
                virtual double integrate(double a, double b, double eps=1e-6) const = 0;

            protected:
                Function f;
        };
    }
}

#endif /* INTEGRATOR_HPP_ */
