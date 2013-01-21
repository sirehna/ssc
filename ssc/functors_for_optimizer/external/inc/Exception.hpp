#ifndef __EXCEPTIONHANDLING__
#define __EXCEPTIONHANDLING__

#include <string>
#include <exception>

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

#define QUOTEME_(x) #x
#define QUOTEME(x) QUOTEME_(x)
//#define THROW(function,exception, message) Exception exception(QUOTEME(__FILE__## ##function## ##__LINE__##: ## message));throw exception;
#define THROW(function,exception, message) exception exc("In file " __FILE__ ", line " QUOTEME(__LINE__) ", function " function ": " message);throw exc;

#endif

