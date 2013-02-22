/*
 * OptimizationProblemTest.hpp
 *
 * \date 21 févr. 2013, 10:14:54
 *  \author cec
 */

#ifndef OPTIMIZATIONPROBLEMTEST_HPP_
#define OPTIMIZATIONPROBLEMTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"

class OptimizationProblemTest : public ::testing::Test
{
    protected:
        OptimizationProblemTest();
	    virtual ~OptimizationProblemTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;
        StatePtr x1,x2,x3,x4;

};

#endif  /* OPTIMIZATIONPROBLEMTEST_HPP_ */
