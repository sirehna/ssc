/*
 * epsilon_algorithm_test.hpp
 *
 *  Created on: May 15, 2014
 *      Author: cady
 */

#ifndef EPSILON_ALGORITHM_TEST_HPP_
#define EPSILON_ALGORITHM_TEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class epsilon_algorithm_test : public ::testing::Test
{
    protected:
        epsilon_algorithm_test();
	    virtual ~epsilon_algorithm_test();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* EPSILON_ALGORITHM_TEST_HPP_ */
