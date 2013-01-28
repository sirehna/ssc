/*
 * PowTest.hpp
 *
 * \date 22 janv. 2013, 08:43:58
 *  \author cec
 */

#ifndef POWTEST_HPP_
#define POWTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class PowTest : public ::testing::Test
{
    protected:
        PowTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* POWTEST_HPP_ */
