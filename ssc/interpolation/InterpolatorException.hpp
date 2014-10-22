#include "ssc/exception_handling/Exception.hpp"

namespace ssc
{
    namespace interpolation
    {
        class InterpolatorException : public ::ssc::exception_handling::Exception
        {
            public:
                InterpolatorException(const char* s) :
                    ::ssc::exception_handling::Exception(s)
                {
                }
        };
    }
}
