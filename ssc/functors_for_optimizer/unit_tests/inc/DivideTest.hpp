/*
 * DivideTest.hpp
 *
 * \date 1 févr. 2013, 08:49:57
 *  \author cec
 */

#ifndef DIVIDETEST_HPP_
#define DIVIDETEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"

class DivideTest : public ::testing::Test
{
    protected:
        DivideTest();
	    virtual ~DivideTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;

};

#endif  /* DIVIDETEST_HPP_ */
