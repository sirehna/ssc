/*
 * SerializeReversePolishTest.hpp
 *
 * \date 28 févr. 2013, 17:02:32
 *  \author cec
 */

#ifndef SERIALIZEREVERSEPOLISHTEST_HPP_
#define SERIALIZEREVERSEPOLISHTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"
#include "SerializeReversePolish.hpp"

class SerializeReversePolishTest : public ::testing::Test
{
    protected:
        SerializeReversePolishTest();
	    virtual ~SerializeReversePolishTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;
		StatePtr x;
		StatePtr y;
		std::stringstream ss;
		SerializeReversePolish serialize;

};

#endif  /* SERIALIZEREVERSEPOLISHTEST_HPP_ */
