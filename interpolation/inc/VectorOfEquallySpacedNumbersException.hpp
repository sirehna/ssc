/*
 * VectorOfEquallySpacedNumberException.hpp
 *
 * \date 12 juin 2013, 15:47:26
 *  \author cec
 */

#ifndef VECTOROFEQUALLYSPACEDNUMBEREXCEPTION_HPP_
#define VECTOROFEQUALLYSPACEDNUMBEREXCEPTION_HPP_

#include "Exception.hpp"

class VectorOfEquallySpacedNumbersException: public Exception {
public:
    VectorOfEquallySpacedNumbersException(const char* s) :
            Exception(s) {
    }
};


#endif  /* VECTOROFEQUALLYSPACEDNUMBEREXCEPTION_HPP_ */
