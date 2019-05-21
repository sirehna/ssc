/*
 * FunctorAlgebraTest.hpp
 *
 * \date 1 févr. 2013, 15:24:54
 * \author cec
 */

#ifndef FUNCTORALGEBRATEST_HPP_
#define FUNCTORALGEBRATEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

class FunctorAlgebraTest : public ::testing::Test
{
    protected:
        FunctorAlgebraTest();
        virtual ~FunctorAlgebraTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        ssc::functors_for_optimizer::StateGenerator generate;
        ssc::functors_for_optimizer::StatePtr x;
        ssc::functors_for_optimizer::StatePtr y;
        ssc::functors_for_optimizer::StatePtr z;
};

#endif  /* FUNCTORALGEBRATEST_HPP_ */
