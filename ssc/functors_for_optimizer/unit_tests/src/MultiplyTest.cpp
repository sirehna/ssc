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

MultiplyTest::MultiplyTest() : a(DataGenerator(99))
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
    StateGenerator generate;
    State x1 = generate.state("x1");
    State x2 = generate.state("x2");
    Multiply m(x1,x2);
//! [MultiplyTest example]
//! [MultiplyTest expected output]
    *x1 = a.random<double>();
    *x2 = a.random<double>();
    ASSERT_DOUBLE_EQ((*x1)*(*x2),m.val()());
//! [MultiplyTest expected output]
}

TEST_F(MultiplyTest, should_be_able_to_multiply_with_Multiply)
{
    StateGenerator generate;
    State x1 = generate.state("x1");
    State x2 = generate.state("x2");
    Multiply m1(x1,x2);
    Multiply m2(x1,m1);
    Multiply m3(m1,x1);
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        *x1 = a.random<double>();
        *x2 = a.random<double>();
        ASSERT_DOUBLE_EQ((*x1)*(*x1)*(*x2),m2.val()());
        ASSERT_DOUBLE_EQ(m3.val()(),m2.val()());
    }
}

TEST_F(MultiplyTest, should_be_able_to_calculate_gradient_simple)
{
    StateGenerator generate;
    State x1 = generate.state("x1");
    State x2 = generate.state("x2");
    Multiply m(x1,x2);
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *x1 = a.random<double>();
        *x2 = a.random<double>();
        auto g = m.grad();
        ASSERT_EQ(2,g.idx.size());
        ASSERT_EQ(2,g.values.size());
        ASSERT_DOUBLE_EQ(*x2, g.values.at(0)());
        ASSERT_DOUBLE_EQ(*x1, g.values.at(1)());
    }
}

TEST_F(MultiplyTest, should_be_able_to_chain_multiplications)
{
    StateGenerator generate;
    State x = generate.state("x");
    const auto m = Multiply(x,Multiply(x,x));
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *x = a.random<double>();
        auto g = m.grad();
        ASSERT_EQ(1,g.idx.size());
        ASSERT_EQ(1,g.values.size());
        ASSERT_DOUBLE_EQ(3.*(*x)*(*x), g.values.at(0)());
    }
}

TEST_F(MultiplyTest, should_be_able_to_calculate_gradient_complex)
{
    StateGenerator generate;
    State x1 = generate.state("x1");
    State x2 = generate.state("x2");
    Multiply m(Multiply(x1,x1),Multiply(x2,Multiply(x2,x2)));
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *x1 = a.random<double>();
        *x2 = a.random<double>();
        auto g = m.grad();
        ASSERT_EQ(2,g.idx.size());
        ASSERT_EQ(2,g.values.size());
        ASSERT_DOUBLE_EQ(2*(*x1)*(*x2)*(*x2)*(*x2), g.values.at(0)());
        ASSERT_DOUBLE_EQ(3*(*x1)*(*x1)*(*x2)*(*x2), g.values.at(1)());
    }
}

