/*
 * Rectangle.hpp
 *
 *  Created on: Nov 28, 2014
 *      Author: cady
 */

#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include "ssc/integrate/Integrator.hpp"

namespace ssc
{
    namespace integrate
    {
        class Rectangle : public Integrator
        {
            public:
                Rectangle();
                Rectangle(const Function& f);

            private:
                double integrate_impl(const Function& f, double a, double b, double eps=1e-6) const;
        };
    }
}
#endif /* RECTANGLE_HPP_ */
