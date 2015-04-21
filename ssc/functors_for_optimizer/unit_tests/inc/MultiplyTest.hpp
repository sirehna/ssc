/*
 * MultiplyTest.hpp
 *
 * \date 23 janv. 2013, 08:22:10
 *  \author cec
 */

#ifndef MULTIPLYTEST_HPP_
#define MULTIPLYTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

class MultiplyTest : public ::testing::Test
{
    protected:
        MultiplyTest();
        virtual ~MultiplyTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        ssc::functors_for_optimizer::StateGenerator generate;
        ssc::functors_for_optimizer::StatePtr x1;
        ssc::functors_for_optimizer::StatePtr x2;
};

#endif  /* MULTIPLYTEST_HPP_ */
