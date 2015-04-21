/*
 * SerializeReversePolishTest.hpp
 *
 * \date 28 f�vr. 2013, 17:02:32
 *  \author cec
 */

#ifndef SERIALIZEREVERSEPOLISHTEST_HPP_
#define SERIALIZEREVERSEPOLISHTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"
#include "ssc/functors_for_optimizer/SerializeReversePolish.hpp"

class SerializeReversePolishTest : public ::testing::Test
{
    protected:
        SerializeReversePolishTest();
        virtual ~SerializeReversePolishTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        ssc::functors_for_optimizer::StateGenerator generate;
        ssc::functors_for_optimizer::StatePtr x;
        ssc::functors_for_optimizer::StatePtr y;
        std::stringstream ss;
        ssc::functors_for_optimizer::SerializeReversePolish serialize;
};

#endif  /* SERIALIZEREVERSEPOLISHTEST_HPP_ */
