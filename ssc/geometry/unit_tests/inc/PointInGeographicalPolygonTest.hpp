/*
 * PointInGeographicalPolygonTest.hpp
 *
 * \date 27 mars 2013, 16:08:18
 *  \author cec
 */

#ifndef POINTINGEOGRAPHICALPOLYGONTEST_HPP_
#define POINTINGEOGRAPHICALPOLYGONTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"

class PointInGeographicalPolygonTest : public ::testing::Test
{
    protected:
        PointInGeographicalPolygonTest();
        virtual ~PointInGeographicalPolygonTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;

};

#endif  /* POINTINGEOGRAPHICALPOLYGONTEST_HPP_ */
