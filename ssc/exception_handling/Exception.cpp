#include <sstream>
#include <cstring>

#include "ssc/exception_handling/Exception.hpp"

::ssc::exception_handling::Exception::Exception(const char* message_):
                               message(message_)
{
}

::ssc::exception_handling::Exception::Exception(const Exception& rhs):
                    message(rhs.message)
{
}

::ssc::exception_handling::Exception::~Exception () throw ()
{
}

const char* ::ssc::exception_handling::Exception::what() const throw()
{
    return message;
}
