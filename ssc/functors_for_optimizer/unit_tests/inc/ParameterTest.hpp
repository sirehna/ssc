/*
 * ConstantTest.hpp
 *
 * \date 31 janv. 2013, 15:25:00
 *  \author cec
 */

#ifndef PARAMETERTEST_HPP_
#define PARAMETERTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"

class ParameterTest : public ::testing::Test
{
    protected:
        ParameterTest();
        virtual ~ParameterTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
};

#endif  /* PARAMETERTEST_HPP_ */
