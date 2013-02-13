/*
 * SimplifyTest.hpp
 *
 * \date 13 févr. 2013, 08:57:17
 *  \author cec
 */

#ifndef SIMPLIFYTEST_HPP_
#define SIMPLIFYTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"

class SimplifyTest : public ::testing::Test
{
    protected:
        SimplifyTest();
	    virtual ~SimplifyTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;
        StatePtr x1;
        StatePtr x2;

};

#endif  /* SIMPLIFYTEST_HPP_ */
