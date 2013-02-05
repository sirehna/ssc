/*
 * ConstantTest.cpp
 *
 * \date 5 févr. 2013, 11:20:51
 *  \author cec
 */

#include "ConstantTest.hpp"
#include "Constant.hpp"
#include "test_macros.hpp"
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
    ASSERT_DOUBLE_EQ(val, c.get_value()());
//! [ConstantTest expected output]
}

TEST_F(ConstantTest, derivative)
{
    StateGenerator generate;
    Constant c(a.random<double>());
    auto x = generate.state(a.random<std::string>());
    auto d = c.diff(x);
    for (size_t i = 0 ; i < 10000 ; ++i)
    {
        **x = a.random<double>();
        ASSERT_DOUBLE_EQ(0, d->get_value()());
    }
}
