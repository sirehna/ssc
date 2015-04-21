/*
 * DivideTest.hpp
 *
 * \date 1 f�vr. 2013, 08:49:57
 *  \author cec
 */

#ifndef DIVIDETEST_HPP_
#define DIVIDETEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

class DivideTest : public ::testing::Test
{
    protected:
        DivideTest();
        virtual ~DivideTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        StateGenerator generate;
        StatePtr x;
        StatePtr y;

};

#endif  /* DIVIDETEST_HPP_ */
