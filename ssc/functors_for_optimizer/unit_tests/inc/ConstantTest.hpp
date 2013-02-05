/*
 * ConstantTest.hpp
 *
 * \date 5 févr. 2013, 11:20:41
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
