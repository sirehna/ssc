/*
 * CosTest.hpp
 *
 * \date 1 févr. 2013, 13:24:30
 * \author cec
 */

#ifndef COSTEST_HPP_
#define COSTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

class CosTest : public ::testing::Test
{
    protected:
        CosTest();
        virtual ~CosTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        ssc::functors_for_optimizer::StateGenerator generate;
};

#endif  /* SINTEST_HPP_ */
