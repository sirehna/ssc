/*
 * SinTest.hpp
 *
 * \date 1 févr. 2013, 13:24:30
 *  \author cec
 */

#ifndef SINTEST_HPP_
#define SINTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"

class SinTest : public ::testing::Test
{
    protected:
        SinTest();
	    virtual ~SinTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;

};

#endif  /* SINTEST_HPP_ */
