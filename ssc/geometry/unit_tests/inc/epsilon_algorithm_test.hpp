/*
 * epsilon_algorithm_test.hpp
 *
 *  Created on: May 15, 2014
 *      Author: cady
 */

#ifndef EPSILON_ALGORITHM_TEST_HPP_
#define EPSILON_ALGORITHM_TEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"

class epsilon_algorithm_test : public ::testing::Test
{
    protected:
        epsilon_algorithm_test();
        virtual ~epsilon_algorithm_test();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;

};

#endif  /* EPSILON_ALGORITHM_TEST_HPP_ */
