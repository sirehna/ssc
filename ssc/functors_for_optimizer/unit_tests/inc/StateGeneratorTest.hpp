#ifndef __SIR_STATE_GENERATOR_TEST__
#define __SIR_STATE_GENERATOR_TEST__

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"

class StateGeneratorTest : public ::testing::Test
{
    protected:
        StateGeneratorTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
};

#endif
