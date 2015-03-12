/*
 * SerializeMapsSetsAndVectors.hpp
 *
 *  Created on: Mar 4, 2015
 *      Author: cady
 */


#ifndef SERIALIZEMAPSSETSANDVECTORS_HPP_
#define SERIALIZEMAPSSETSANDVECTORS_HPP_

#ifdef _GLIBCXX_VECTOR
#include <ostream>
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& m)
{
    os << "[";
    if (not(m.empty())) os << m.front();
    for (size_t i = 1 ; i < m.size() ; ++i)
    {
        os << ", " << m.at(i);
    }
    os << "]";
    return os;
}
#endif

#ifdef _GLIBCXX_MAP
#include <ostream>
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::map<T,U>& m)
{
    os << "{";
    if (not(m.empty())) os << m.begin()->first << ": " << m.begin()->second;
    for (auto it = m.begin() ; it != m.end() ; ++it)
    {
        if (it!=m.begin()) os << ", " << it->first << ": " << it->second;
    }
    os << "}";
    return os;
}
#endif

#ifdef _STL_PAIR_H
#include <ostream>
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& m)
{
    os << "(" << m.first << "," << m.second << ")";
    return os;
}
#endif

#ifdef _GLIBCXX_SET
#include <ostream>
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& m)
{
    os << "{";
    if (not(m.empty())) os << *m.begin();
    for (auto it = m.begin() ; it != m.end() ; ++it)
    {
        if (it!=m.begin()) os << ", " << *it;
    }
    os << "}";
    return os;
}
#endif

#endif  /* SERIALIZEMAPSSETSANDVECTORS_HPP_ */
