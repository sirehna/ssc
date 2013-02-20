/*
 * SplineFunctorTest.hpp
 *
 * \date 18 févr. 2013, 12:47:00
 *  \author cec
 */

#ifndef SPLINEFUNCTORTEST_HPP_
#define SPLINEFUNCTORTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class SplineFunctorTest : public ::testing::Test
{
    protected:
        SplineFunctorTest();
	    virtual ~SplineFunctorTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* SPLINEFUNCTORTEST_HPP_ */
