/*
 * IpoptSolverTest.hpp
 *
 * \date 22 févr. 2013, 15:28:07
 *  \author cec
 */

#ifndef IPOPTSOLVERTEST_HPP_
#define IPOPTSOLVERTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"

class IpoptSolverTest : public ::testing::Test
{
    protected:
        IpoptSolverTest();
	    virtual ~IpoptSolverTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;
		StatePtr x1, x2, x3, x4;
};

#endif  /* IPOPTSOLVERTEST_HPP_ */
