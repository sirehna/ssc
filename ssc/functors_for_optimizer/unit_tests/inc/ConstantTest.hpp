/*
 * ConstantTest.hpp
 *
 * \date 5 f�vr. 2013, 11:20:41
 *  \author cec
 */

#ifndef CONSTANTTEST_HPP_
#define CONSTANTTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"

class ConstantTest : public ::testing::Test
{
    protected:
        ConstantTest();
        virtual ~ConstantTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;

};

#endif  /* CONSTANTTEST_HPP_ */
