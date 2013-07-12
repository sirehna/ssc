/*
 * ConstantTest.cpp
 *
 * \date 5 févr. 2013, 11:20:51
 *  \author cec
 */

#include "ConstantTest.hpp"
#include "Constant.hpp"
#include "StateGenerator.hpp"

ConstantTest::ConstantTest() :
        a(DataGenerator(7777))
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
    const double val = a.random<double>();
    Constant c(val);
//! [ConstantTest example]
//! [ConstantTest expected output]
    ASSERT_DOUBLE_EQ(val, c.get_lambda()());
//! [ConstantTest expected output]
}

TEST_F(ConstantTest, should_be_able_to_state_a_constant_is_null_or_equal_to_a_double)
{
    StateGenerator generate;
    const double cst = a.random<double>().but_not(0);
    Constant c(cst);
    ASSERT_EQ(c, cst);
    ASSERT_TRUE(Constant(0).is_null());
    ASSERT_FALSE(c.is_null());
}

TEST_F(ConstantTest, derivative)
{
    StateGenerator generate;
    Constant c(a.random<double>());
    auto x = generate.state(a.random<std::string>());
    auto d = c.diff(x);
    for (size_t i = 0 ; i < 10000 ; ++i)
    {
        *x = a.random<double>();
        ASSERT_DOUBLE_EQ(0, d->get_lambda()());
    }
}

TEST_F(ConstantTest, equality_operator)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const Constant c1(a.random<double>()), c2(a.random<double>());
        ASSERT_TRUE(c1.equals(c1));
        ASSERT_FALSE(c1.equals(c2));
        ASSERT_FALSE(c2.equals(c1));
    }
}
