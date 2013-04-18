/*
 * PiecewiseConstantVariableStep.hpp
 *
 * \date 11 avr. 2013, 08:44:04
 *  \author cec
 */

#ifndef PIECEWISECONSTANTVARIABLESTEPTEST_HPP_
#define PIECEWISECONSTANTVARIABLESTEPTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class PiecewiseConstantVariableStepTest : public ::testing::Test
{
    protected:
        PiecewiseConstantVariableStepTest();
	    virtual ~PiecewiseConstantVariableStepTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* PIECEWISECONSTANTVARIABLESTEPTEST_HPP_ */
