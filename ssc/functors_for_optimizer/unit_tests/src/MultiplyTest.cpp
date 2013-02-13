/*
 * MultiplyTest.cpp
 *
 * \date 23 janv. 2013, 08:21:46
 *  \author cec
 */

#include "MultiplyTest.hpp"
#include "StateGenerator.hpp"
#include "Multiply.hpp"

#include "FunctorAlgebra.hpp"
#include "test_macros.hpp"
#include "Serialize.hpp"

MultiplyTest::MultiplyTest() : a(DataGenerator(99)), generate(StateGenerator()), x1(generate.state("x1")), x2(generate.state("x2"))
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
    **x1 = a.random<double>();
    **x2 = a.random<double>();
    Multiply m(x1,x2);
//! [MultiplyTest example]
//! [MultiplyTest expected output]
    ASSERT_DOUBLE_EQ((**x1)*(**x2),m.get_value()());
//! [MultiplyTest expected output]
}

TEST_F(MultiplyTest, should_be_able_to_multiply_with_Multiply)
{
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

TEST_F(MultiplyTest, bug_after_introducing_n_ary_operators)
{
    Mult m1(new Multiply(x1,x2));
    std::stringstream ss;
    Serialize s(ss);
    m1->diff(x2)->accept(s);
    ASSERT_EQ("x1", ss.str());
}

TEST_F(MultiplyTest, derivative)
{
    Mult m1(new Multiply(x1,x2));
    Multiply m2(x1,m1);
    auto dm2_dx1 = m2.diff(x1);
    auto dm2_dx2 = m2.diff(x2);
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        **x1 = a.random<double>();
        **x2 = a.random<double>();
        ASSERT_DOUBLE_EQ(2*(**x1)*(**x2),dm2_dx1->get_value()());
        ASSERT_DOUBLE_EQ((**x1)*(**x1),dm2_dx2->get_value()());
    }
}

TEST_F(MultiplyTest, bug_in_remove_ones_and_zeros)
{
    auto dx2dx2_x1 = x2->diff(x2)*x1;
    std::stringstream ss;
    Serialize s(ss);
    dx2dx2_x1->accept(s);
    ASSERT_EQ("x1", ss.str());
}

TEST_F(MultiplyTest, bug_in_diff)
{
    auto df = ((x1 * x1) * x1)->diff(x1);
    std::stringstream ss;
    Serialize s(ss);
    df->accept(s);
    ASSERT_EQ("((x1 * (x1 + x1)) + (x1 * x1))", ss.str());
}

TEST_F(MultiplyTest, bug_02)
{
    StateGenerator generate;
    auto x = generate.state("x");
    std::vector<NodePtr> sons;
    sons.push_back(x);
    Multiply m(sons);
    std::stringstream ss;
    Serialize s(ss);
    m.diff(x)->accept(s);
    ASSERT_EQ("1", ss.str());
}
