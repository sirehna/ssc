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

class IntegrateOscillatoryTest : public ::testing::Test
{
    protected:
        IntegrateOscillatoryTest();
        virtual ~IntegrateOscillatoryTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
};

#endif  /* INTEGRATEOSCILLATORYTEST_HPP_ */
