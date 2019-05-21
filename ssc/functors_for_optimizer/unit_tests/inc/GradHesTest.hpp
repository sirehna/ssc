/*
 * GradHesTest.hpp
 *
 * \date 20 févr. 2013, 11:46:39
 * \author cec
 */

#ifndef GRADHESTEST_HPP_
#define GRADHESTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

class GradHesTest : public ::testing::Test
{
    protected:
        GradHesTest();
        virtual ~GradHesTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        ssc::functors_for_optimizer::StateGenerator generate;
        ssc::functors_for_optimizer::StatePtr x1,x2,x3,x4;
        ssc::functors_for_optimizer::NodePtr f;
        std::vector<ssc::functors_for_optimizer::NodePtr> g;
};

#endif  /* GRADHESTEST_HPP_ */
