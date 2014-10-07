#ifndef TEXTFILEREADEREXCEPTION
#define TEXTFILEREADEREXCEPTION

#include "ssc/exception_handling/Exception.hpp"

class TextFileReaderException: public Exception
{
    public:
        TextFileReaderException(const char* s) :
                Exception(s)
        {
        }
};


#endif
