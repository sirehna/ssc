/*
 * Simpson.hpp
 *
 * \date 23 avr. 2013, 15:39:50
 *  \author cec
 */

#ifndef SIMPSON_HPP_
#define SIMPSON_HPP_
#include <functional>
#include <tr1/memory>
typedef std::function<double (const double&)> Function;


/** \author cec
 *  \ingroup quadpack
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet quadpack/unit_tests/src/SimpsonTest.cpp SimpsonTest example
 *  \section ex2 Expected output
 *  \snippet quadpack/unit_tests/src/SimpsonTest.cpp SimpsonTest expected output
 */
class Simpson
{
    public:
        Simpson(const Function& f);
        double integrate(const double& a, const double& b, const double& eps=1e-6) const;
    private:
        class Impl;
        std::tr1::shared_ptr<Impl> pimpl;
};

#endif /* SIMPSON_HPP_ */
