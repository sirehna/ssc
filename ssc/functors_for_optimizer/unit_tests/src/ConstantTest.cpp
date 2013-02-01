/*
 * ConstantTest.cpp
 *
 * \date 31 janv. 2013, 15:25:10
 *  \author cec
 */

#include "ConstantTest.hpp"
#include "Constant.hpp"
#include "StateGenerator.hpp"
#include "test_macros.hpp"

ConstantTest::ConstantTest() : a(DataGenerator(123))
{
}

ConstantTest::~ConstantTest()
{
}

void ConstantTest::SetUp()
{
}

void ConstantTest::TearDown()
{
}

TEST_F(ConstantTest, example)
{
//! [ConstantTest example]
    Constant c(a.random<double>());
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

TEST_F(ConstantTest, derivative_is_always_zero)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const Constant n(a.random<double>());
        StateGenerator generate;
        auto x = generate.state("x");
        ASSERT_EQ(0, n.diff(x)->get_value()());
    }
}


