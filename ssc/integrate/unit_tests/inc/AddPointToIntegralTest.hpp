/*
 * AddPointToIntegralTest.hpp
 *
 * \date 10 juin 2013, 10:04:15
 *  \author cec
 */

#ifndef ADDPOINTTOINTEGRALTEST_HPP_
#define ADDPOINTTOINTEGRALTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class AddPointToIntegralTest : public ::testing::Test
{
    protected:
        AddPointToIntegralTest();
	    virtual ~AddPointToIntegralTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* ADDPOINTTOINTEGRALTEST_HPP_ */
