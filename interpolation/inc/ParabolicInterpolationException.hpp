/*
 * ParabolicInterpolationException.hpp
 *
 * \date 12 juin 2013, 16:14:58
 *  \author cec
 */

#ifndef PARABOLICINTERPOLATIONEXCEPTION_HPP_
#define PARABOLICINTERPOLATIONEXCEPTION_HPP_

#include "Exception.hpp"

class ParabolicInterpolationException : public Exception
{
    public:
        ParabolicInterpolationException(const char* s) :
                Exception(s)
        {
        }
};



#endif  /* PARABOLICINTERPOLATIONEXCEPTION_HPP_ */
