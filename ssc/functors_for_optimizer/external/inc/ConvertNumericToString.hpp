#ifndef __CONVERTNUMERICTOSTRING__
#define __CONVERTNUMERICTOSTRING__
#include <iomanip>
#include <sstream>
#include <string>
#include <math.h>
#include <iostream>


template <class T>
inline std::string convert_to_string(const T& t)
{
    std::ostringstream strs;
    strs << std::setprecision(5);
    strs.setf(std::ios::scientific,std::ios::floatfield);
    strs << t;
    std::string str = strs.str();
    return str;
}

template <>
inline std::string convert_to_string<bool>(const bool& t)
{
    if (t) return "true";
    return "false";
}

#endif
