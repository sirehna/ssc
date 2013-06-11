/*
 * MinimizeSplineTest.hpp
 *
 * \date 10 juin 2013, 11:47:58
 *  \author cec
 */

#ifndef MINIMIZESPLINETEST_HPP_
#define MINIMIZESPLINETEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class MinimizeSplineTest : public ::testing::Test
{
    protected:
        MinimizeSplineTest();
	    virtual ~MinimizeSplineTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* MINIMIZESPLINETEST_HPP_ */
