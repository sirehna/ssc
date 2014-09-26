/*
 * epsilon_algorithm_test.cpp
 *
 *  Created on: May 15, 2014
 *      Author: cady
 */

#include "epsilon_algorithm_test.hpp"
#include "epsilon_algorithm.hpp"
#include "test_macros.hpp"
epsilon_algorithm_test::epsilon_algorithm_test() : a(DataGenerator(211))
{
}

epsilon_algorithm_test::~epsilon_algorithm_test()
{
}

void epsilon_algorithm_test::SetUp()
{
}

void epsilon_algorithm_test::TearDown()
{
}

TEST_F(epsilon_algorithm_test, example)
{
//! [epsilon_algorithm_test example]
    std::vector<double> S(1,1);
    const size_t N = 25;
    for (size_t i = 1 ; i < N ; ++i)
    {
        S.push_back(S.back()+pow(-1,i)/(2.*i+1));
    }
//! [epsilon_algorithm_test example]
//! [epsilon_algorithm_test expected output]
    ASSERT_DOUBLE_EQ(atan(1), epsilon_algorithm(S));
//! [epsilon_algorithm_test expected output]
}



