#ifndef __SIR_STATE_GENERATOR_TEST__
#define __SIR_STATE_GENERATOR_TEST__


#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class StateGeneratorTest : public ::testing::Test
{
    protected:
        StateGeneratorTest();
        virtual void SetUp();
        virtual void TearDown();
        DataGenerator a;

};

#endif
