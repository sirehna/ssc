/*
 * ValidateAgainstCSVTest.hpp
 *
 * \date 8 avr. 2012, 14:10:21
 *  \author cec
 */

#ifndef VALIDATEAGAINSTCSVTEST_HPP_
#define VALIDATEAGAINSTCSVTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class ValidateAgainstCSVTest : public ::testing::Test
{
    protected:
        ValidateAgainstCSVTest();
	    virtual ~ValidateAgainstCSVTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* VALIDATEAGAINSTCSVTEST_HPP_ */
