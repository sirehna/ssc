/*
 * SumTest.hpp
 *
 * \date 31 janv. 2013, 16:02:07
 *  \author cec
 */

#ifndef SUMTEST_HPP_
#define SUMTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

class SumTest : public ::testing::Test
{
    protected:
        SumTest();
        virtual ~SumTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        ssc::functors_for_optimizer::StateGenerator generate;
};

#endif  /* SUMTEST_HPP_ */
