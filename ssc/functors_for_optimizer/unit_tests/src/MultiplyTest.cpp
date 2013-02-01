/*
 * MultiplyTest.cpp
 *
 * \date 23 janv. 2013, 08:21:46
 *  \author cec
 */

#include "MultiplyTest.hpp"
#include "StateGenerator.hpp"
#include "Multiply.hpp"
#include "test_macros.hpp"

MultiplyTest::MultiplyTest() : a(DataGenerator(99)), generate(StateGenerator())
{
}

MultiplyTest::~MultiplyTest()
{
}

void MultiplyTest::SetUp()
{
}

void MultiplyTest::TearDown()
{
}

TEST_F(MultiplyTest, example)
{
//! [MultiplyTest example]
    auto x1 = generate.state("x1");
    auto x2 = generate.state("x2");
    Multiply m(x1,x2);
//! [MultiplyTest example]
//! [MultiplyTest expected output]
    **x1 = a.random<double>();
    **x2 = a.random<double>();
    ASSERT_DOUBLE_EQ((**x1)*(**x2),m.get_value()());
//! [MultiplyTest expected output]
}

TEST_F(MultiplyTest, should_be_able_to_multiply_with_Multiply)
{
    auto x1 = generate.state("x1");
    auto x2 = generate.state("x2");
    Mult m1(new Multiply(x1,x2));
    Multiply m2(x1,m1);
    Multiply m3(m1,x1);
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        **x1 = a.random<double>();
        **x2 = a.random<double>();
        ASSERT_DOUBLE_EQ((**x1)*(**x1)*(**x2),m2.get_value()());
        ASSERT_DOUBLE_EQ(m3.get_value()(),m2.get_value()());
    }
}

TEST_F(MultiplyTest, derivative)
{
    StateGenerator generate;
    auto x1 = generate.state("x1");
    auto x2 = generate.state("x2");
    Mult m1(new Multiply(x1,x2));
    Multiply m2(x1,m1);
    Multiply m3(m1,x1);
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        **x1 = a.random<double>();
        **x2 = a.random<double>();
        ASSERT_DOUBLE_EQ(2*(**x1)*(**x2),m2.diff(x1)->get_value()());
        ASSERT_DOUBLE_EQ((**x1)*(**x1),m2.diff(x2)->get_value()());
    }
}
