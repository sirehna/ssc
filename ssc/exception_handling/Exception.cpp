#include <sstream>
#include <cstring>

#include "ssc/exception_handling/Exception.hpp"

Exception::Exception(const char* message_):
                               message(message_)
{
}

Exception::Exception(const Exception& rhs):
                    message(rhs.message)
{
}

Exception::~Exception () throw ()
{
}

const char* Exception::what() const throw()
{
    return message;
}
