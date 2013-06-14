#ifndef __SPLINESEXCEPTION_HPP__
#define __SPLINESEXCEPTION_HPP__


#include "Exception.hpp"
class SplinesException: public Exception {
public:
    SplinesException(const char* s) :
            Exception(s) {
    }
};

#endif
