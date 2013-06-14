#include "Exception.hpp"

class InterpolatorException : public Exception
{
    public:
        InterpolatorException(const char* s) :
                Exception(s)
        {
        }
};
