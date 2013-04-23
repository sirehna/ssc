/*
 * TrapezoidalIntegration.hpp
 *
 * \date 23 avr. 2013, 14:47:21
 *  \author cec
 */

#ifndef TRAPEZOIDALINTEGRATION_HPP_
#define TRAPEZOIDALINTEGRATION_HPP_

#include <functional>
#include <tr1/memory>
typedef std::function<double (const double&)> Function;

/** \author cec
 *  \brief This class was created to
 *  \ingroup quadpack
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet quadpack/unit_tests/src/TrapezoidalIntegrationTest.cpp TrapezoidalIntegrationTest example
 *  \section ex2 Expected output
 *  \snippet quadpack/unit_tests/src/TrapezoidalIntegrationTest.cpp TrapezoidalIntegrationTest expected output
 */

class TrapezoidalIntegration
{
    public:
        TrapezoidalIntegration(const Function& f);
        double integrate(const double& a, const double& b, const size_t& nb_of_evaluations) const;

    private:
        class Impl;
        std::tr1::shared_ptr<Impl> pimpl;
};

#endif /* TRAPEZOIDALINTEGRATION_HPP_ */
