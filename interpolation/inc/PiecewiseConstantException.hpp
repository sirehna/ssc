/*
 * SplinesException.hpp
 *
 * \date 13 juin 2013, 11:04:40
 *  \author cec
 */

#ifndef PIECEWISECONSTANTEXCEPTION_HPP_
#define PIECEWISECONSTANTEXCEPTION_HPP_

#include "Exception.hpp"

class PiecewiseConstantException : public Exception
{
    public:
        PiecewiseConstantException(const char* s) :
                Exception(s)
        {
        }
};


#endif  /* PIECEWISECONSTANTEXCEPTION_HPP_ */
