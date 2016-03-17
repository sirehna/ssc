#ifndef __CONVERTNUMERICTOSTRING__
#define __CONVERTNUMERICTOSTRING__
#include <iomanip>
#include <sstream>
#include <string>
#include <math.h>
#include <iostream>
#include <limits>

template <class T>
inline std::string convert_to_string(const T& t)
{
    std::ostringstream strs;
    strs << std::setprecision(16);
    //strs << std::setprecision(std::numeric_limits<float>::digits10);
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
