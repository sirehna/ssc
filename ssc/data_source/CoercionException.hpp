/*
 * CoercionException.hpp
 *
 * \date 18 june 2013, 14:37:43
 *  \author cec
 */

#ifndef COERCIONEXCEPTION_HPP_
#define COERCIONEXCEPTION_HPP_

#include "ssc/exception_handling/Exception.hpp"

namespace ssc
{
    namespace data_source
    {
        class CoercionException : public ::ssc::exception_handling::Exception
        {
            public:
                CoercionException(const char* s) :
                        Exception(s)
                {
                }
        };
    }
}


#endif  /* COERCIONEXCEPTION_HPP_ */
