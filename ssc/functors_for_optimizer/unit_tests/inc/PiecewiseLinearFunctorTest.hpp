/*
 * PiecewiseLinearFunctorTest.hpp
 *
 * \date 19 févr. 2013, 08:34:35
 *  \author cec
 */

#ifndef PIECEWISELINEARFUNCTORTEST_HPP_
#define PIECEWISELINEARFUNCTORTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"

class PiecewiseLinearFunctorTest : public ::testing::Test
{
    protected:
        PiecewiseLinearFunctorTest();
	    virtual ~PiecewiseLinearFunctorTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;

};

#endif  /* PIECEWISELINEARFUNCTORTEST_HPP_ */
