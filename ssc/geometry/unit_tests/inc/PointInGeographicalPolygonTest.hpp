/*
 * PointInGeographicalPolygonTest.hpp
 *
 * \date 27 mars 2013, 16:08:18
 *  \author cec
 */

#ifndef POINTINGEOGRAPHICALPOLYGONTEST_HPP_
#define POINTINGEOGRAPHICALPOLYGONTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class PointInGeographicalPolygonTest : public ::testing::Test
{
    protected:
        PointInGeographicalPolygonTest();
	    virtual ~PointInGeographicalPolygonTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* POINTINGEOGRAPHICALPOLYGONTEST_HPP_ */
