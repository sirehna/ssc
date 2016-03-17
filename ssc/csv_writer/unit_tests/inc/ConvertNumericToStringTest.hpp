#ifndef __SIR_CONVERTNUMERICTOSTRINGTEST__
#define __SIR_CONVERTNUMERICTOSTRINGTEST__

#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "ssc/csv_writer/ConvertNumericToString.hpp"

class ConvertNumericToStringTest : public ::testing::Test
{
    protected:
        ConvertNumericToStringTest(){}
        virtual void SetUp();
        virtual void TearDown();
        size_t nb_of_zeros_in_exponents_on_current_platform() const;
};

#endif
