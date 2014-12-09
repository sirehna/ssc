/*
 * IntegrateOscillatory.hpp
 *
 *  Created on: Dec 9, 2014
 *      Author: cady
 */

#ifndef INTEGRATEOSCILLATORY_HPP_
#define INTEGRATEOSCILLATORY_HPP_

#include "ssc/integrate/QuadPack.hpp"

namespace ssc
{
    namespace integrate
    {
        class IntegrateOscillatory : public QuadPack
        {
            public:
                IntegrateOscillatory();
                IntegrateOscillatory(const Function& f_);

            private:
                double integrate_impl(const Function& f, double a, double b, double eps=1e-6) const;
        };
    }
}

#endif /* INTEGRATEOSCILLATORY_HPP_ */
