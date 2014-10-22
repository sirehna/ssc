/*
 * DataSourceException.hpp
 *
 * \date 17 juin 2013, 11:13:11
 *  \author cec
 */

#ifndef DATASOURCEEXCEPTION_HPP_
#define DATASOURCEEXCEPTION_HPP_

#include "ssc/exception_handling/Exception.hpp"

namespace ssc
{
    namespace data_source
    {
        class DataSourceException : public ::ssc::exception_handling::Exception
        {
            public:
                DataSourceException(const char* s) :
                    ::ssc::exception_handling::Exception(s)
                {
                }
        };
    }
}

#endif  /* DATASOURCEEXCEPTION_HPP_ */
