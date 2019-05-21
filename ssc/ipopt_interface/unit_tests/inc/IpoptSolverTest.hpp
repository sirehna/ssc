/*
 * IpoptSolverTest.hpp
 *
 * \date 22 févr. 2013, 15:28:07
 * \author cec
 */

#ifndef IPOPTSOLVERTEST_HPP_
#define IPOPTSOLVERTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

class IpoptSolverTest : public ::testing::Test
{
    protected:
        IpoptSolverTest();
        virtual ~IpoptSolverTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        ssc::functors_for_optimizer::StateGenerator generate;
        ssc::functors_for_optimizer::StatePtr x1, x2, x3, x4;
};

#endif  /* IPOPTSOLVERTEST_HPP_ */
