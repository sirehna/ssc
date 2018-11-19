#ifndef RAPIDJSONHPP
#define RAPIDJSONHPP

#include <iostream>

#include "ssc/exception_handling/Exception.hpp"

class JSONException: public ssc::exception_handling::Exception
{
    public:
        InvalidInputException(const std::string& message, const std::string& file, const std::string& function, const unsigned int line) :
               Exception(message, file, function, line)
        {
        }
};

#define RAPIDJSON_ASSERT(x) \
   if (not(x))\
   {\
      if (strcmp("IsArray()", #x) == 0 )\
      {\
          throw JSONException("Expecting an array", __FILE__, __PRETTY_FUNCTION__, __LINE__);\
      }\
      else\
      {\
         throw JSONException(#x, __FILE__, __PRETTY_FUNCTION__, __LINE__);\
      }\
   }
   //std::cout << "in file " << __FILE__ << ", line " << __LINE__ << ": " << #x << std::endl
//#include <stdexcept>               // std::runtime_error
//#include "rapidjson/error/error.h" // rapidjson::ParseResult
/*struct ParseException : std::runtime_error, rapidjson::ParseResult
{
    ParseException(rapidjson::ParseErrorCode code, const char* msg, size_t offset) : std::runtime_error(msg), ParseResult(code, offset)
    {}

    virtual ~ParseException() {}
};
*/

#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"



#endif
