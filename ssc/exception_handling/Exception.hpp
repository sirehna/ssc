#ifndef __EXCEPTIONHANDLING__
#define __EXCEPTIONHANDLING__

#include <string>
#include <exception>
#include <iostream>

namespace ssc
{
    namespace exception_handling
    {
        class Exception : public std::exception
        {
            public:
                Exception(const char* message_);
                Exception(const Exception& rhs);

                ~Exception () throw ();

                virtual const char* what() const throw();

            private:
                Exception();
                Exception& operator=(const Exception& rhs);
                const char* message;
        };
    }
}

#define QUOTEME_(x) #x
#define QUOTEME(x) QUOTEME_(x)
#define THROW(function,exception, message)\
    std::string __msg215("In file " __FILE__ ", line " QUOTEME(__LINE__) ", function ");\
    __msg215 += function;\
    __msg215 += ": ";\
    __msg215 += message;\
    exception exc(__msg215.c_str());\
    throw exc;
#endif

