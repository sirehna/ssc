/*
 * QuadPackTest.hpp
 *
 * \date 5 juil. 2013, 13:31:57
 *  \author cec
 */

#ifndef QUADPACKTEST_HPP_
#define QUADPACKTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"

class QuadPackTest : public ::testing::Test
{
    protected:
        QuadPackTest();
        virtual ~QuadPackTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;

};

#endif  /* QUADPACKTEST_HPP_ */
