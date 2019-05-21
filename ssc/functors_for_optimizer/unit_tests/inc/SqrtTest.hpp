/*
 * SqrtTest.hpp
 *
 * \date Mar 8, 2016
 * \author cec
 */


#ifndef FUNCTORS_FOR_OPTIMIZER_UNIT_TESTS_INC_SQRTTEST_HPP_
#define FUNCTORS_FOR_OPTIMIZER_UNIT_TESTS_INC_SQRTTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

class SqrtTest : public ::testing::Test
{
    protected:
        SqrtTest();
        virtual ~SqrtTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        ssc::functors_for_optimizer::StateGenerator generate;
};

#endif  /* FUNCTORS_FOR_OPTIMIZER_UNIT_TESTS_INC_SQRTTEST_HPP_ */
