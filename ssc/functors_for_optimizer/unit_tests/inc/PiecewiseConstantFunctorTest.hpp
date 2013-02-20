/*
 * PiecewiseConstantFunctor.hpp
 *
 * \date 18 févr. 2013, 17:19:11
 *  \author cec
 */

#ifndef PIECEWISECONSTANTFUNCTORTEST_HPP_
#define PIECEWISECONSTANTFUNCTORTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"

class PiecewiseConstantFunctorTest : public ::testing::Test
{
    protected:
        PiecewiseConstantFunctorTest();
	    virtual ~PiecewiseConstantFunctorTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;

};

#endif  /* PIECEWISECONSTANTFUNCTORTEST_HPP_ */
