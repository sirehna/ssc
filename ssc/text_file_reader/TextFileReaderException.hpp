#ifndef TEXTFILEREADEREXCEPTION
#define TEXTFILEREADEREXCEPTION

#include "ssc/exception_handling/Exception.hpp"

class TextFileReaderException: public ::ssc::exception_handling::Exception
{
    public:
        TextFileReaderException(const char* s) :
            ::ssc::exception_handling::Exception(s)
        {
        }
};


#endif
