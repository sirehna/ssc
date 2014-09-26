/*
 * NullTest.hpp
 *
 * \date 31 janv. 2013, 15:16:38
 *  \author cec
 */

#ifndef NULLTEST_HPP_
#define NULLTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class NullTest : public ::testing::Test
{
    protected:
        NullTest();
	    virtual ~NullTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* NULLTEST_HPP_ */
