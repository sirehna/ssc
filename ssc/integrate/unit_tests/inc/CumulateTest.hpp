/*
 * CumulateTest.hpp
 *
 * \date 8 oct. 2013, 08:21:58
 *  \author cec
 */

#ifndef CUMULATETEST_HPP_
#define CUMULATETEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class CumulateTest : public ::testing::Test
{
    protected:
        CumulateTest();
	    virtual ~CumulateTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* CUMULATETEST_HPP_ */
