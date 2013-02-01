/*
 * SerializeTest.hpp
 *
 * \date 1 févr. 2013, 09:56:53
 *  \author cec
 */

#ifndef SERIALIZETEST_HPP_
#define SERIALIZETEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"

class SerializeTest : public ::testing::Test
{
    protected:
        SerializeTest();
	    virtual ~SerializeTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;
		std::stringstream ss;

};

#endif  /* SERIALIZETEST_HPP_ */
