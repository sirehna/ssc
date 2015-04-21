/*
 * PiecewiseConstantFunctor.hpp
 *
 * \date 18 f�vr. 2013, 17:19:11
 *  \author cec
 */

#ifndef PIECEWISECONSTANTFUNCTORTEST_HPP_
#define PIECEWISECONSTANTFUNCTORTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "StateGenerator.hpp"

class PiecewiseConstantFunctorTest : public ::testing::Test
{
    protected:
        PiecewiseConstantFunctorTest();
        virtual ~PiecewiseConstantFunctorTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        StateGenerator generate;
};

#endif  /* PIECEWISECONSTANTFUNCTORTEST_HPP_ */
