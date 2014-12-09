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
        class ClenshawCurtis : public QuadPack
        {
            public:
                ClenshawCurtis(const double tau);
                ClenshawCurtis(const Function& f, const double tau);
                ~ClenshawCurtis();
                ClenshawCurtis(const ClenshawCurtis& rhs);
                ClenshawCurtis& operator=(const ClenshawCurtis& rhs);

            private:
                ClenshawCurtis();
                double integrate_impl(const Function& f, double a, double b, double eps=1e-6);
                double tau;
                int nb_of_chebychev_moments;
                int nb_of_calls;
                double *chebychev_moments;
                double *alist;
                double *blist;
                double *rlist;
                double *elist;
                int *iord;
                int *nnlog;
        };
    }
}

#endif /* INTEGRATEOSCILLATORY_HPP_ */
