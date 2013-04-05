/*
 * LongitudeLatitudeTest.hpp
 *
 * \date 28 mars 2013, 11:30:25
 *  \author cec
 */

#ifndef LONGITUDELATITUDETEST_HPP_
#define LONGITUDELATITUDETEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class LongitudeLatitudeTest : public ::testing::Test
{
    protected:
        LongitudeLatitudeTest();
	    virtual ~LongitudeLatitudeTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* LONGITUDELATITUDETEST_HPP_ */
