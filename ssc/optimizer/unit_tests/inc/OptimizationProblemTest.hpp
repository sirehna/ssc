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

class OptimizationProblemTest : public ::testing::Test
{
    protected:
        OptimizationProblemTest();
	    virtual ~OptimizationProblemTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* OPTIMIZATIONPROBLEMTEST_HPP_ */
