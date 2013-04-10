/*
 * TrackTest.hpp
 *
 * \date 8 avr. 2013, 15:16:12
 *  \author cec
 */

#ifndef TRACKTEST_HPP_
#define TRACKTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class TrackTest : public ::testing::Test
{
    protected:
        TrackTest();
	    virtual ~TrackTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* TRACKTEST_HPP_ */
