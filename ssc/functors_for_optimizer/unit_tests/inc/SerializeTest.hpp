/*
 * SerializeTest.hpp
 *
 * \date 1 févr. 2013, 09:56:53
 * \author cec
 */

#ifndef SERIALIZETEST_HPP_
#define SERIALIZETEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

class SerializeTest : public ::testing::Test
{
    protected:
        SerializeTest();
        virtual ~SerializeTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        ssc::functors_for_optimizer::StateGenerator generate;
        std::stringstream ss;
};

#endif  /* SERIALIZETEST_HPP_ */
