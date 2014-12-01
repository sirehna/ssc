/*
 * IntegratorException.hpp
 *
 *  Created on: Dec 1, 2014
 *      Author: cady
 */

#ifndef INTEGRATOREXCEPTION_HPP_
#define INTEGRATOREXCEPTION_HPP_

#include "ssc/exception_handling/Exception.hpp"

class IntegratorException: public ssc::exception_handling::Exception
{
    public:
        IntegratorException(const char* s) :
                Exception(s)
        {
        }
};

#endif /* INTEGRATOREXCEPTION_HPP_ */
