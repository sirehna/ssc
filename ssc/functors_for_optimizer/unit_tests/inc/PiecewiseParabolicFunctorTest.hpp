/*
 * PiecewiseParabolicFunctorTest.hpp
 *
 * \date 19 f�vr. 2013, 14:43:09
 *  \author cec
 */

#ifndef PIECEWISEPARABOLICFUNCTORTEST_HPP_
#define PIECEWISEPARABOLICFUNCTORTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "StateGenerator.hpp"

class PiecewiseParabolicFunctorTest : public ::testing::Test
{
    protected:
        PiecewiseParabolicFunctorTest();
        virtual ~PiecewiseParabolicFunctorTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        StateGenerator generate;
};

#endif  /* PIECEWISEPARABOLICFUNCTORTEST_HPP_ */
