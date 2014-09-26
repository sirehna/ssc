/*
 * loxodrome_on_ellipsoidTest.hpp
 *
 *  Created on: May 12, 2014
 *      Author: cady
 */

#ifndef LOXODROME_ON_ELLIPSOIDTEST_HPP_
#define LOXODROME_ON_ELLIPSOIDTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class loxodrome_on_ellipsoidTest : public ::testing::Test
{
    protected:
        loxodrome_on_ellipsoidTest();
	    virtual ~loxodrome_on_ellipsoidTest();
        virtual void SetUp();
        virtual void TearDown();


        DataGenerator a;
		double latitude_of_Murray_Spring;
        double longitude_of_Murray_Spring;
        double latitude_of_Wauka_1978;
        double longitude_of_Wauka_1978;
        double inverse_flattening;
        double semi_major_axis;
};

#endif  /* LOXODROME_ON_ELLIPSOIDTEST_HPP_ */
