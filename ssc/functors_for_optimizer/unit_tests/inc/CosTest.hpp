/*
 * SinTest.hpp
 *
 * \date 1 févr. 2013, 13:24:30
 *  \author cec
 */

#ifndef COSTEST_HPP_
#define COSTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"

class CosTest : public ::testing::Test
{
    protected:
        CosTest();
	    virtual ~CosTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;

};

#endif  /* SINTEST_HPP_ */
