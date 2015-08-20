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
        IntegratorException(const std::string& message, const std::string& file, const std::string& function, const unsigned int line) :
                                        Exception(message, file, function, line)
        {
        }
};

#endif /* INTEGRATOREXCEPTION_HPP_ */
