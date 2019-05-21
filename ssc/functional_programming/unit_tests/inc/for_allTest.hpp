/*
 * for_allTest.hpp
 *
 * \date 19 juil. 2013, 11:52:22
 * \author cec
 */

#ifndef FOR_ALLTEST_HPP_
#define FOR_ALLTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class for_allTest : public ::testing::Test
{
    protected:
        for_allTest();
        virtual ~for_allTest();
        virtual void SetUp();
        virtual void TearDown();
        DataGenerator a;

};

#endif  /* FOR_ALLTEST_HPP_ */
