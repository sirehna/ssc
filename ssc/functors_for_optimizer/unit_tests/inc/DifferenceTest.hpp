/*
 * DifferenceTest.hpp
 *
 * \date 1 févr. 2013, 09:20:05
 *  \author cec
 */

#ifndef DIFFERENCETEST_HPP_
#define DIFFERENCETEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"

class DifferenceTest : public ::testing::Test
{
    protected:
        DifferenceTest();
	    virtual ~DifferenceTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;

};

#endif  /* DIFFERENCETEST_HPP_ */
