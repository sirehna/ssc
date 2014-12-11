/*
 * Burcher.hpp
 *
 *  Created on: Dec 11, 2014
 *      Author: cady
 */

#ifndef BURCHER_HPP_
#define BURCHER_HPP_

#include "ssc/integrate/Integrator.hpp"

namespace ssc
{
    namespace integrate
    {
        class Burcher : public Integrator
        {
            public:
                Burcher();
                Burcher(const Function& f);
                double integrate_n_steps(const Function& f, double a, double b, size_t n);

            private:
                double integrate_impl(const Function& f, double a, double b, double eps=1e-6);
        };
    }
}

#endif /* BURCHER_HPP_ */
