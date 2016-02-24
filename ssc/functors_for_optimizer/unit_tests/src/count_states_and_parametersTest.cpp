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
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/macros/test_macros.hpp"

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

TEST_F(count_states_and_parametersTest, can_get_number_of_states)
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

TEST_F(count_states_and_parametersTest, can_get_number_of_parameters)
{
    StateGenerator generate;
    auto x = generate.state("x");
    auto k = generate.parameter(25);
    auto p = generate.parameter(2.5);
    auto m = generate.parameter(3.5);
    auto z = generate.state("z");
    ASSERT_EQ(2, max_parameter_index(k*x+p*z+m));
}

TEST_F(count_states_and_parametersTest, can_differentiate_between_one_or_no_states)
{
    // If max state index is 0, we can't tell if we have only one state or zero
    StateGenerator generate;
    auto k = generate.parameter(25);
    auto p = generate.parameter(2.5);
    auto m = generate.parameter(3.5);
    ASSERT_FALSE(there_are_states(k*p+m));
    auto z = generate.state("z");
    ASSERT_TRUE(there_are_states(k*p+m*z));
}

TEST_F(count_states_and_parametersTest, can_differentiate_between_one_or_no_parameters)
{
    // If max parameter index is 0, we can't tell if we have only one parameter or zero
    StateGenerator generate;
    auto x = generate.state("x");
    auto y = generate.state("y");
    auto z = generate.state("z");
    ASSERT_FALSE(there_are_parameters(x*y+z));
    auto p = generate.parameter(2.5);
    auto m = generate.parameter(3.5);
    ASSERT_TRUE(there_are_parameters(p+m*z));
}
