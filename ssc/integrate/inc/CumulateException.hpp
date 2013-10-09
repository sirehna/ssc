/*
 * CumulateException.hpp
 *
 * \date 8 oct. 2013, 08:36:56
 *  \author cec
 */

#ifndef CUMULATEEXCEPTION_HPP_
#define CUMULATEEXCEPTION_HPP_

#include "Exception.hpp"

class CumulateException : public Exception
{
    public:
        CumulateException(const char* s) :
                Exception(s)
        {
        }
};


#endif /* CUMULATEEXCEPTION_HPP_ */
