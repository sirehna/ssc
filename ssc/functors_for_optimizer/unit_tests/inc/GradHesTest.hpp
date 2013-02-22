/*
 * GradHesTest.hpp
 *
 * \date 20 févr. 2013, 11:46:39
 *  \author cec
 */

#ifndef GRADHESTEST_HPP_
#define GRADHESTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class GradHesTest : public ::testing::Test
{
    protected:
        GradHesTest();
	    virtual ~GradHesTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* GRADHESTEST_HPP_ */
