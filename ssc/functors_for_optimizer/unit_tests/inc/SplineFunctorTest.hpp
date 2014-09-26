/*
 * CubicSplineFunctorTest.hpp
 *
 * \date 19 févr. 2013, 09:37:52
 *  \author cec
 */

#ifndef SPLINEFUNCTORTEST_HPP_
#define SPLINEFUNCTORTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"

class SplineFunctorTest : public ::testing::Test
{
    protected:
        SplineFunctorTest();
	    virtual ~SplineFunctorTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;

};

#endif  /* SPLINEFUNCTORTEST_HPP_ */
