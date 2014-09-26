/*
 * MultiplyTest.hpp
 *
 * \date 23 janv. 2013, 08:22:10
 *  \author cec
 */

#ifndef MULTIPLYTEST_HPP_
#define MULTIPLYTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"

class MultiplyTest : public ::testing::Test
{
    protected:
        MultiplyTest();
	    virtual ~MultiplyTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;
		StatePtr x1;
		StatePtr x2;

};

#endif  /* MULTIPLYTEST_HPP_ */
