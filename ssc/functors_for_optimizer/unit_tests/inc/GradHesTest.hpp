/*
 * GradHesTest.hpp
 *
 * \date 20 f�vr. 2013, 11:46:39
 *  \author cec
 */

#ifndef GRADHESTEST_HPP_
#define GRADHESTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "StateGenerator.hpp"

class GradHesTest : public ::testing::Test
{
    protected:
        GradHesTest();
        virtual ~GradHesTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        StateGenerator generate;
        StatePtr x1,x2,x3,x4;
        NodePtr f;
        std::vector<NodePtr> g;
};

#endif  /* GRADHESTEST_HPP_ */
