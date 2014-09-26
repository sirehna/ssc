/*
 * FunctorAlgebraTest.hpp
 *
 * \date 1 févr. 2013, 15:24:54
 *  \author cec
 */

#ifndef FUNCTORALGEBRATEST_HPP_
#define FUNCTORALGEBRATEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include "StateGenerator.hpp"

class FunctorAlgebraTest : public ::testing::Test
{
    protected:
        FunctorAlgebraTest();
	    virtual ~FunctorAlgebraTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;
		StateGenerator generate;
		StatePtr x;
		StatePtr y;
		StatePtr z;

};

#endif  /* FUNCTORALGEBRATEST_HPP_ */
