/*
 * StateGetterTest.hpp
 *
 * \date 20 févr. 2013, 12:43:53
 * \author cec
 */

#ifndef STATEGETTERTEST_HPP_
#define STATEGETTERTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"

class StateGetterTest : public ::testing::Test
{
    protected:
        StateGetterTest();
        virtual ~StateGetterTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
};

#endif  /* STATEGETTERTEST_HPP_ */
