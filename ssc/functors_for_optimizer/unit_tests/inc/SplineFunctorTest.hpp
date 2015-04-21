/*
 * CubicSplineFunctorTest.hpp
 *
 * \date 19 f�vr. 2013, 09:37:52
 *  \author cec
 */

#ifndef SPLINEFUNCTORTEST_HPP_
#define SPLINEFUNCTORTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

class SplineFunctorTest : public ::testing::Test
{
    protected:
        SplineFunctorTest();
        virtual ~SplineFunctorTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        StateGenerator generate;
};

#endif  /* SPLINEFUNCTORTEST_HPP_ */
