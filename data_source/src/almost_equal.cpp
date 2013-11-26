/*
 * almost_equal.cpp
 *
 * \date 26 nov. 2013, 11:22:57
 *  \author cec
 */

#include "almost_equal.hpp"

template <> bool almost_equal(const double& t1, const double& t2)
{
    return t1==t2;
}
