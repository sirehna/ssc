/*
 * ConstantTest.cpp
 *
 * \date 31 janv. 2013, 15:25:10
 *  \author cec
 */

#include "ParameterTest.hpp"
#include "Parameter.hpp"
#include "StateGenerator.hpp"
#include "test_macros.hpp"

ParameterTest::ParameterTest() : a(DataGenerator(123))
{
}

ParameterTest::~ParameterTest()
{
}

void ParameterTest::SetUp()
{
}

void ParameterTest::TearDown()
{
}

TEST_F(ParameterTest, example)
{
//! [ConstantTest example]
    Parameter c(a.random<double>());
    for (size_t i = 0 ; i < 10000 ; ++i)
    {
        const double val = a.random<double>();
        *c = val;
        ASSERT_DOUBLE_EQ(val, c.get_value()());
    }

//! [ConstantTest example]
//! [ConstantTest expected output]
//! [ConstantTest expected output]
}

TEST_F(ParameterTest, derivative_is_always_zero)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const Parameter n(a.random<double>());
        StateGenerator generate;
        auto x = generate.state("x");
        ASSERT_EQ(0, n.diff(x)->get_value()());
    }
}


