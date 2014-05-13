/*
 * LegTest.hpp
 *
 * \date 9 avr. 2013, 14:54:00
 *  \author cec
 */

#ifndef LEGTEST_HPP_
#define LEGTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class ShortestPathLegTest : public ::testing::Test
{
    protected:
        ShortestPathLegTest();
	    virtual ~ShortestPathLegTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* LEGTEST_HPP_ */
