/*
 * IntegrateOscillatoryTest.hpp
 *
 *  Created on: Dec 9, 2014
 *      Author: cady
 */


#ifndef INTEGRATEOSCILLATORYTEST_HPP_
#define INTEGRATEOSCILLATORYTEST_HPP_

#include "gtest/gtest.h"
#include <ssc/random_data_generator/DataGenerator.hpp>

class ClenshawCurtisTest : public ::testing::Test
{
    protected:
        ClenshawCurtisTest();
        virtual ~ClenshawCurtisTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
};

#endif  /* INTEGRATEOSCILLATORYTEST_HPP_ */
