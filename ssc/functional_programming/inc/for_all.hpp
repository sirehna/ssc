/*
 * for_all.hpp
 *
 * \date 19 juil. 2013, 12:09:00
 *  \author cec
 */

#ifndef FOR_ALL_HPP_
#define FOR_ALL_HPP_

#include <algorithm>
#include <functional>

template <typename T,typename F> std::vector<T> for_all(const std::vector<T>& v, const F& f)
{
    std::vector<T> ret;
    std::transform(v.begin(), v.end(),std::back_inserter(ret),f);
    return ret;
}

#endif  /* FOR_ALL_HPP_ */
