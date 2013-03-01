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

class IpoptSolverTest : public ::testing::Test
{
    protected:
        IpoptSolverTest();
	    virtual ~IpoptSolverTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* IPOPTSOLVERTEST_HPP_ */
