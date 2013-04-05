/*
 * PointInCartesianPolygonTest.hpp
 *
 * \date 27 mars 2013, 16:07:53
 *  \author cec
 */

#ifndef POINTINCARTESIANPOLYGONTEST_HPP_
#define POINTINCARTESIANPOLYGONTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class PointInCartesianPolygonTest : public ::testing::Test
{
    protected:
        PointInCartesianPolygonTest();
	    virtual ~PointInCartesianPolygonTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* POINTINCARTESIANPOLYGONTEST_HPP_ */
