/*
 * SumTest.hpp
 *
 * \date 31 janv. 2013, 16:02:07
 *  \author cec
 */

#ifndef SUMTEST_HPP_
#define SUMTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"

class SumTest : public ::testing::Test
{
    protected:
        SumTest();
	    virtual ~SumTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;

};

#endif  /* SUMTEST_HPP_ */
