/*
 * count_states_and_parametersTest.cpp
 *
 * \date Feb 24, 2016
 * \author cec
 */


#include "StateAndParameterCounterTest.hpp"
#include "ssc/functors_for_optimizer/StateAndParameterCounter.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"
#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"
#include "ssc/functors_for_optimizer/Sum.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/macros/test_macros.hpp"

using namespace ssc::functors_for_optimizer;

StateAndParameterCounterTest::StateAndParameterCounterTest() : a(ssc::random_data_generator::DataGenerator(81515412))
{
}

StateAndParameterCounterTest::~StateAndParameterCounterTest()
{
}

void StateAndParameterCounterTest::SetUp()
{
}

void StateAndParameterCounterTest::TearDown()
{
}

TEST_F(StateAndParameterCounterTest, can_get_number_of_states)
{
//! [StateAndParameterCounterTest example]
    StateGenerator generate;
    auto x = generate.state("x");
    auto y = generate.state("y");
    auto z = generate.state("z");
//! [StateAndParameterCounterTest example]
//! [StateAndParameterCounterTest expected output]
    ASSERT_EQ(2, StateAndParameterCounter(x+y+z).max_state_index());
//! [count_states_and_parametersTest expected output]
}

TEST_F(StateAndParameterCounterTest, can_get_number_of_parameters)
{
    StateGenerator generate;
    auto x = generate.state("x");
    auto k = generate.parameter(25);
    auto p = generate.parameter(2.5);
    auto m = generate.parameter(3.5);
    auto z = generate.state("z");
    ASSERT_EQ(2, StateAndParameterCounter(k*x+p*z+m).max_parameter_index());
}

TEST_F(StateAndParameterCounterTest, can_differentiate_between_one_or_no_states)
{
    // If max state index is 0, we can't tell if we have only one state or zero
    StateGenerator generate;
    auto k = generate.parameter(25);
    auto p = generate.parameter(2.5);
    auto m = generate.parameter(3.5);
    ASSERT_FALSE(StateAndParameterCounter(k*p+m).there_are_states());
    auto z = generate.state("z");
    ASSERT_TRUE(StateAndParameterCounter(k*p+m*z).there_are_states());
}

TEST_F(StateAndParameterCounterTest, can_differentiate_between_one_or_no_parameters)
{
    // If max parameter index is 0, we can't tell if we have only one parameter or zero
    StateGenerator generate;
    auto x = generate.state("x");
    auto y = generate.state("y");
    auto z = generate.state("z");
    ASSERT_FALSE(StateAndParameterCounter(x*y+z).there_are_parameters());
    auto p = generate.parameter(2.5);
    auto m = generate.parameter(3.5);
    ASSERT_TRUE(StateAndParameterCounter(p+m*z).there_are_parameters());
}
