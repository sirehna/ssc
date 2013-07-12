/*
 * TypeCoercion.hpp
 *
 * \date 17 juin 2013, 14:50:54
 *  \author cec
 */

#ifndef TYPECOERCION_HPP_
#define TYPECOERCION_HPP_


#include <vector>
#include <list>

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

template<class T> struct is_arithmetic { const static bool value = false; };
#define DECLARE_ARITHMETIC_TYPE(t) template<> struct is_arithmetic<t> { const static bool value = true; }

DECLARE_ARITHMETIC_TYPE(bool);
DECLARE_ARITHMETIC_TYPE(char);
DECLARE_ARITHMETIC_TYPE(wchar_t);
DECLARE_ARITHMETIC_TYPE(short);
DECLARE_ARITHMETIC_TYPE(int);
DECLARE_ARITHMETIC_TYPE(long);
DECLARE_ARITHMETIC_TYPE(float);
DECLARE_ARITHMETIC_TYPE(double);
DECLARE_ARITHMETIC_TYPE(size_t);





/** \author: cec
 *  \ingroup data_source
 *  \brief Converts type to list of doubles
 *  \snippet data_source/unit_tests/src/TypeCoercionTest.cpp example
*/

template <class T>
typename enable_if<is_arithmetic<T>::value,void>::type coerce(std::list<double>& ret, const T thing_to_convert)
{
    ret.push_back(thing_to_convert);
}

template <typename T> void coerce(std::list<double>& ret, const std::vector<T>& thing_to_convert)
{
    for (typename std::vector<T>::const_iterator it = thing_to_convert.begin() ; it != thing_to_convert.end() ; ++it)
    {
        coerce(ret, *it);
    }
}



#endif /* TYPECOERCION_HPP_ */
