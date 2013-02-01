/*
 * LnTest.hpp
 *
 * \date 1 févr. 2013, 12:29:31
 *  \author cec
 */

#ifndef LNTEST_HPP_
#define LNTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"

class LnTest : public ::testing::Test
{
    protected:
        LnTest();
	    virtual ~LnTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;

};

#endif  /* LNTEST_HPP_ */
