/*
 * SplinesException.hpp
 *
 * \date 13 juin 2013, 11:04:40
 *  \author cec
 */

#ifndef PIECEWISECONSTANTEXCEPTION_HPP_
#define PIECEWISECONSTANTEXCEPTION_HPP_

#include "ssc/exception_handling/Exception.hpp"

namespace ssc
{
    namespace interpolation
    {
        class PiecewiseConstantException : public ::ssc::exception_handling::Exception
        {
            public:
                PiecewiseConstantException(const char* s) :
                    ::ssc::exception_handling::Exception(s)
                {
                }
        };
    }
}

#endif  /* PIECEWISECONSTANTEXCEPTION_HPP_ */
