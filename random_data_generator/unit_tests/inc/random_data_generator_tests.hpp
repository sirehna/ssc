#ifndef RANDOM_DATA_GENERATOR_TESTS_HPP
#define RANDOM_DATA_GENERATOR_TESTS_HPP

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class DataGeneratorTests : public ::testing::Test
{
    protected:
        DataGeneratorTests() : a(DataGenerator(95442))
                                {}
        virtual void SetUp();
        virtual void TearDown();
        DataGenerator a;

};



#endif
