/*
 * CoercionException.hpp
 *
 * \date 18 juin 2013, 14:37:43
 *  \author cec
 */

#ifndef COERCIONEXCEPTION_HPP_
#define COERCIONEXCEPTION_HPP_

#include "Exception.hpp"

class CoercionException : public Exception
{
    public:
        CoercionException(const char* s) :
                Exception(s)
        {
        }
};


#endif  /* COERCIONEXCEPTION_HPP_ */
