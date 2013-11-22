/*
 * IpoptSolverException.hpp
 *
 * \date 21 nov. 2013, 09:08:24
 *  \author cec
 */

#ifndef IPOPTSOLVEREXCEPTION_HPP_
#define IPOPTSOLVEREXCEPTION_HPP_

#include "Exception.hpp"

class IpoptSolverException : public Exception
{
    public:
        IpoptSolverException(const char* s) :
                Exception(s)
        {
        }
};

#endif  /* IPOPTSOLVEREXCEPTION_HPP_ */
