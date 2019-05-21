/*
 * DifferenceTest.hpp
 *
 * \date 1 févr. 2013, 09:20:05
 * \author cec
 */

#ifndef DIFFERENCETEST_HPP_
#define DIFFERENCETEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

class DifferenceTest : public ::testing::Test
{
    protected:
        DifferenceTest();
        virtual ~DifferenceTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        ssc::functors_for_optimizer::StateGenerator generate;
};

#endif  /* DIFFERENCETEST_HPP_ */
