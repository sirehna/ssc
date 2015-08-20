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
                Exception(const std::string& message, const std::string& file, const std::string& function, const unsigned int line);
                Exception(const Exception& rhs);

                ~Exception () throw ();

                virtual const char* what() const throw();
                std::string get_message() const;

            private:
                Exception();
                Exception& operator=(const Exception& rhs);
                std::string full_message;
                std::string short_message;
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
    exception exc(message, __FILE__, function, __LINE__);\
    throw exc;
#endif

