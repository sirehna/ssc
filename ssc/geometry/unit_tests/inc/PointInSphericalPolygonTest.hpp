/*
 * PointInSphericalPolygonTest.hpp
 *
 * \date 27 mars 2013, 16:08:05
 *  \author cec
 */

#ifndef POINTINSPHERICALPOLYGONTEST_HPP_
#define POINTINSPHERICALPOLYGONTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class PointInSphericalPolygonTest : public ::testing::Test
{
    protected:
        PointInSphericalPolygonTest();
	    virtual ~PointInSphericalPolygonTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* POINTINSPHERICALPOLYGONTEST_HPP_ */
