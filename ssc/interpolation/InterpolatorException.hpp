#include "ssc/exception_handling/Exception.hpp"

namespace ssc
{
    namespace interpolation
    {
        class InterpolatorException : public Exception
        {
            public:
                InterpolatorException(const char* s) :
                        Exception(s)
                {
                }
        };
    }
}
