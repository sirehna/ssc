/*
 * Burcher.hpp
 *
 *  Created on: Dec 11, 2014
 *      Author: cady
 */

#ifndef BURCHER_HPP_
#define BURCHER_HPP_

#include <cstddef>
#include <vector>

#include "ssc/integrate/Integrator.hpp"
#include <stddef.h>

namespace ssc
{
    namespace integrate
    {
        class Burcher : public Integrator
        {
            public:
                Burcher();
                Burcher(const Function& f);
                Burcher(const Function& f, const double tau);
                double integrate(const std::vector<double>& omegas) const;
                double integrate_n_steps(const Function& f, double a, double b, size_t n);
                double compute_for(const double tau, const double a, const double b, const double eps);

            private:
                double integrate_impl(const Function& f, double a, double b, double eps=1e-6);
                double tau;
        };
    }
}

#endif /* BURCHER_HPP_ */
