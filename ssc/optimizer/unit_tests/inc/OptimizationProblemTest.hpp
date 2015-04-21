/*
 * OptimizationProblemTest.hpp
 *
 * \date 21 f�vr. 2013, 10:14:54
 *  \author cec
 */

#ifndef OPTIMIZATIONPROBLEMTEST_HPP_
#define OPTIMIZATIONPROBLEMTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

class OptimizationProblemTest : public ::testing::Test
{
    protected:
        OptimizationProblemTest();
        virtual ~OptimizationProblemTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        ssc::functors_for_optimizer::StateGenerator generate;
        ssc::functors_for_optimizer::StatePtr x1,x2,x3,x4;
};

#endif  /* OPTIMIZATIONPROBLEMTEST_HPP_ */
