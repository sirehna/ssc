#ifndef __SIR_CONVERTNUMERICTOSTRINGTEST__
#define __SIR_CONVERTNUMERICTOSTRINGTEST__

#include "ssc/csv_writer/ConvertNumericToString.hpp"
#include "gtest/gtest.h"
#include <string>
#include <vector>


class ConvertNumericToStringTest : public ::testing::Test
{
    protected:
        ConvertNumericToStringTest(){}
        virtual void SetUp();
        virtual void TearDown();
        size_t nb_of_zeros_in_exponents_on_current_platform() const;
};

#endif
