/*
 * System.hpp
 *
 *  Created on: Feb 17, 2021
 *      Author: cady
 */

#ifndef SOLVER_SYSTEM_HPP_
#define SOLVER_SYSTEM_HPP_

#include <vector>

namespace ssc
{
    namespace solver
    {
        class ContinuousSystem
        {
            public:
                ContinuousSystem() : state() {}
                virtual ~ContinuousSystem() = default;
                virtual void operator()(const std::vector<double>& x, std::vector<double>& dx_dt, const double t) = 0;
                std::vector<double> state;
        };
    }
}



#endif /* SOLVER_SYSTEM_HPP_ */
