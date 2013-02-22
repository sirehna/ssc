/*
 * GradHesTest.hpp
 *
 * \date 20 févr. 2013, 11:46:39
 *  \author cec
 */

#ifndef GRADHESTEST_HPP_
#define GRADHESTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"

class GradHesTest : public ::testing::Test
{
    protected:
        GradHesTest();
	    virtual ~GradHesTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;
		StatePtr x1,x2,x3,x4;
		NodePtr f;
		std::vector<NodePtr> g;
};

#endif  /* GRADHESTEST_HPP_ */
