/*
 * ConstantTest.hpp
 *
 * \date 31 janv. 2013, 15:25:00
 *  \author cec
 */

#ifndef CONSTANTTEST_HPP_
#define CONSTANTTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class ConstantTest : public ::testing::Test
{
    protected:
        ConstantTest();
	    virtual ~ConstantTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* CONSTANTTEST_HPP_ */
