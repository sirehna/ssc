/*
 * KinematicsException.hpp
 *
 *  Created on: 7 avr. 2014
 *      Author: cec
 */

#ifndef KINEMATICSEXCEPTION_HPP_
#define KINEMATICSEXCEPTION_HPP_

#include "ssc/exception_handling/Exception.hpp"

namespace ssc
{
    namespace kinematics
    {
        class KinematicsException: public ::ssc::exception_handling::Exception
        {
            public:
                KinematicsException(const char* s) :
                    ::ssc::exception_handling::Exception(s)
                {
                }
        };
    }
}

#endif /* KINEMATICSEXCEPTION_HPP_ */
