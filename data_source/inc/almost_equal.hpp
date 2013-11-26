/*
 * almost_equal.hpp
 *
 * \date 26 nov. 2013, 08:40:25
 *  \author cec
 */

#ifndef ALMOST_EQUAL_HPP_
#define ALMOST_EQUAL_HPP_

template <class T>
bool almost_equal(const T& t1, const T& t2)
{
        (void) t1;
        (void) t2;
    return false;
}

template <> bool almost_equal(const double& t1, const double& t2);


#endif /* ALMOST_EQUAL_HPP_ */
