/*
 * epsilon_algorithm.h
 *
 *  Created on: May 15, 2014
 *      Author: cady
 */

#ifndef EPSILON_ALGORITHM_H_
#define EPSILON_ALGORITHM_H_

#include <vector>

namespace ssc
{
    namespace geometry
    {
        /**  \author cec
          *  \date May 15, 2014, 3:06:32 PM
          *  \brief Finds the limit of a series in the case where only
          *         the first N+1 terms are known
          *  \details Applies the epsilon-algorithm to the
          *           sequence of partial sums of a series supplied on input.
          *           Adapted from *The epsilon algorithm and related topics*,
          *           P.R. Graves-Morris, D.E. Roberts, A. Salam,
          *           Journal of Computational and Applied Mathematics 122 (2000) 51-80
          *           For further details, please see:
          *           T. Mishonov and E. Penev
          *           Int. J. Mod. Phys. B 14, 3831 (2000).
          *  \returns Extrapolated limit
          *  \snippet geometry/unit_tests/src/epsilon_algorithmTest.cpp epsilon_algorithmTest epsilon_algorithm_example
          */
        double epsilon_algorithm(std::vector<double> S //<! Partial sums of the series we wish to extrapolate
                                );
    }
}

#endif /* EPSILON_ALGORITHM_H_ */
