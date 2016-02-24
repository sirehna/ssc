/*
 * count_states_and_parametersTest.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: cady
 */


#include "count_states_and_parametersTest.hpp"
#include "ssc/functors_for_optimizer/count_states_and_parameters.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"
#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"
#include "ssc/functors_for_optimizer/Sum.hpp"

using namespace ssc::functors_for_optimizer;

count_states_and_parametersTest::count_states_and_parametersTest() : a(ssc::random_data_generator::DataGenerator(81515412))
{
}

count_states_and_parametersTest::~count_states_and_parametersTest()
{
}

void count_states_and_parametersTest::SetUp()
{
}

void count_states_and_parametersTest::TearDown()
{
}

TEST_F(count_states_and_parametersTest, example)
{
//! [count_states_and_parametersTest example]
    StateGenerator generate;
    auto x = generate.state("x");
    auto y = generate.state("y");
    auto z = generate.state("z");
//! [count_states_and_parametersTest example]
//! [count_states_and_parametersTest expected output]
    ASSERT_EQ(2, max_state_index(x+y+z));
//! [count_states_and_parametersTest expected output]
}



