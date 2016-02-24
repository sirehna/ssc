/*
 * count_states_and_parametersTest.hpp
 *
 *  Created on: Feb 24, 2016
 *      Author: cady
 */


#ifndef FUNCTORS_FOR_OPTIMIZER_UNIT_TESTS_INC_COUNT_STATES_AND_PARAMETERSTEST_HPP_
#define FUNCTORS_FOR_OPTIMIZER_UNIT_TESTS_INC_COUNT_STATES_AND_PARAMETERSTEST_HPP_

#include "gtest/gtest.h"
#include <ssc/random_data_generator/DataGenerator.hpp>

class count_states_and_parametersTest : public ::testing::Test
{
    protected:
        count_states_and_parametersTest();
        virtual ~count_states_and_parametersTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
};

#endif  /* FUNCTORS_FOR_OPTIMIZER_UNIT_TESTS_INC_COUNT_STATES_AND_PARAMETERSTEST_HPP_ */
