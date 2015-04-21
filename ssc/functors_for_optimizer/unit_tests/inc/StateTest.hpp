#ifndef __SIR_STATESTEST__
#define __SIR_STATESTEST__


#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"

class StateTest : public ::testing::Test
{
    protected:
        StateTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
};

#endif
