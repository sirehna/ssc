/*
 * PiecewiseParabolicFunctorTest.hpp
 *
 * \date 19 févr. 2013, 14:43:09
 * \author cec
 */

#ifndef PIECEWISEPARABOLICFUNCTORTEST_HPP_
#define PIECEWISEPARABOLICFUNCTORTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

class PiecewiseParabolicFunctorTest : public ::testing::Test
{
    protected:
        PiecewiseParabolicFunctorTest();
        virtual ~PiecewiseParabolicFunctorTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        ssc::functors_for_optimizer::StateGenerator generate;
};

#endif  /* PIECEWISEPARABOLICFUNCTORTEST_HPP_ */
