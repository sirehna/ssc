/*
 * IntegrateTest.hpp
 *
 * \date 23 avr. 2013, 09:46:45
 *  \author cec
 */

#ifndef INTEGRATETEST_HPP_
#define INTEGRATETEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class IntegrateTest : public ::testing::Test
{
    protected:
        IntegrateTest();
	    virtual ~IntegrateTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* INTEGRATETEST_HPP_ */
