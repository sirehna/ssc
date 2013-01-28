/*
 * NodeSerializationVisitorTest.hpp
 *
 * \date 28 janv. 2013, 12:22:44
 *  \author cec
 */

#ifndef NODESERIALIZATIONVISITORTEST_HPP_
#define NODESERIALIZATIONVISITORTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"

class NodeSerializationVisitorTest : public ::testing::Test
{
    protected:
        NodeSerializationVisitorTest();
	    virtual ~NodeSerializationVisitorTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;

};

#endif  /* NODESERIALIZATIONVISITORTEST_HPP_ */
