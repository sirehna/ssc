#ifndef __PARAMETER_TEST__
#define __PARAMETER_TEST__


#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class ParameterTest : public ::testing::Test
{
    protected:
        ParameterTest();
        virtual void SetUp();
        virtual void TearDown();
        DataGenerator a;

};

#endif
