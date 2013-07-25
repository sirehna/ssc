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

#include "Exception.hpp"

class For_all_exception : public Exception
{
    public:
        For_all_exception(const char* s) :
                Exception(s)
        {
        }
};


template <typename T,typename F> std::vector<T> for_all(const std::vector<T>& v, const F& f)
{
    std::vector<T> ret;
    std::transform(v.begin(), v.end(),std::back_inserter(ret),f);
    return ret;
}

template <typename T, typename F> std::vector<T> for_all(const std::vector<T>& v1, const std::vector<T>& v2, const F& f)
{
    if (v1.size() != v2.size())
    {
        THROW(__PRETTY_FUNCTION__, For_all_exception, "v1 & v2 should have the same size.");


    }
    std::vector<T> ret;
    std::transform(v1.begin(), v1.end(), v2.begin(), std::back_inserter(ret),f);
    return ret;
}

#endif  /* FOR_ALL_HPP_ */
