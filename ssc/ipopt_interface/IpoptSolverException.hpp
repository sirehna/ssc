/*
 * IpoptSolverException.hpp
 *
 * \date 21 nov. 2013, 09:08:24
 * \author cec
 */

#ifndef IPOPTSOLVEREXCEPTION_HPP_
#define IPOPTSOLVEREXCEPTION_HPP_

#include "ssc/exception_handling/Exception.hpp"

class IpoptSolverException : public ssc::exception_handling::Exception
{
    public:
        IpoptSolverException(const std::string& message, const std::string& file, const std::string& function, const unsigned int line) :
            Exception(message, file, function, line)
        {
        }
};

#endif  /* IPOPTSOLVEREXCEPTION_HPP_ */
