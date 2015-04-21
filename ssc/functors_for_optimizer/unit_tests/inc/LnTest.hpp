/*
 * LnTest.hpp
 *
 * \date 1 f�vr. 2013, 12:29:31
 *  \author cec
 */

#ifndef LNTEST_HPP_
#define LNTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

class LnTest : public ::testing::Test
{
    protected:
        LnTest();
        virtual ~LnTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        ssc::functors_for_optimizer::StateGenerator generate;
};

#endif  /* LNTEST_HPP_ */
