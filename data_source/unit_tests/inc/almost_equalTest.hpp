/*
 * almost_equalTest.hpp
 *
 * \date 26 nov. 2013, 08:41:26
 *  \author cec
 */

#ifndef ALMOST_EQUALTEST_HPP_
#define ALMOST_EQUALTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class almost_equalTest : public ::testing::Test
{
    protected:
        almost_equalTest();
	    virtual ~almost_equalTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* ALMOST_EQUALTEST_HPP_ */
