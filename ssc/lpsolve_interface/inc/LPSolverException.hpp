/*
 * LPSolverException.hpp
 *
 * \date 20 nov. 2013, 16:09:25
 * \author cec
 */

#ifndef LPSOLVEREXCEPTION_HPP_
#define LPSOLVEREXCEPTION_HPP_

#include "Exception.hpp"

class LPSolverException : public Exception
{
    public:
        LPSolverException(const char* s) :
                Exception(s)
        {
        }
};

#endif  /* LPSOLVEREXCEPTION_HPP_ */
