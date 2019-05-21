/*
 * PowTest.hpp
 *
 * \date 22 janv. 2013, 08:43:58
 * \author cec
 */

#ifndef POWTEST_HPP_
#define POWTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

class PowTest : public ::testing::Test
{
    protected:
        PowTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        ssc::functors_for_optimizer::StateGenerator generate;
};

#endif  /* POWTEST_HPP_ */
