#ifndef __SIR_STATESTEST__
#define __SIR_STATESTEST__


#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class StateTest : public ::testing::Test
{
    protected:
        StateTest();
        virtual void SetUp();
        virtual void TearDown();
        DataGenerator a;

};

#endif
