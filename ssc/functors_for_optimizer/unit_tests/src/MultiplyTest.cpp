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
#include "Serialize.hpp"

MultiplyTest::MultiplyTest() : a(ssc::random_data_generator::DataGenerator(99)),
                               generate(StateGenerator()),
                               x1(generate.state("x1")),
                               x2(generate.state("x2"))
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
    *x1 = a.random<double>();
    *x2 = a.random<double>();
    Multiply m(x1,x2);
//! [MultiplyTest example]
//! [MultiplyTest expected output]
    ASSERT_DOUBLE_EQ((x1->get_lambda()())*(x2->get_lambda()()),m.get_lambda()());
//! [MultiplyTest expected output]
}

TEST_F(MultiplyTest, should_be_able_to_multiply_with_Multiply)
{
    Mult m1(new Multiply(x1,x2));
    Multiply m2(x1,m1);
    Multiply m3(m1,x1);
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        *x1 = a.random<double>();
        *x2 = a.random<double>();
        ASSERT_DOUBLE_EQ((x1->get_lambda()())*(x1->get_lambda()())*(x2->get_lambda()()),m2.get_lambda()());
        ASSERT_DOUBLE_EQ(m3.get_lambda()(),m2.get_lambda()());
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
        *x1 = a.random<double>();
        *x2 = a.random<double>();
        ASSERT_DOUBLE_EQ(2*(x1->get_lambda()())*(x2->get_lambda()()),dm2_dx1->get_lambda()());
        ASSERT_DOUBLE_EQ((x1->get_lambda()())*(x1->get_lambda()()),dm2_dx2->get_lambda()());
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
    ASSERT_EQ("x1 * x1 + x1 * x1 + x1 * x1", ss.str());
}

TEST_F(MultiplyTest, bug_02)
{
    std::vector<NodePtr> sons;
    sons.push_back(x1);
    Multiply m(sons);
    std::stringstream ss;
    Serialize s(ss);
    m.diff(x1)->accept(s);
    ASSERT_EQ("1", ss.str());
}

TEST_F(MultiplyTest, should_be_able_to_get_the_factors_in_a_product_of_two)
{
    Mult m(new Multiply(x1,x2));
    auto factors = m->get_factors();
    ASSERT_EQ(2,factors.size());
    ASSERT_EQ(*x1,*factors.at(0));
    ASSERT_EQ(*x2,*factors.at(1));
}

TEST_F(MultiplyTest, should_be_able_to_get_the_factors_in_a_product_of_three)
{
    auto x3 = generate.state("x3");
    auto m = x1*x2*x3;
    auto factors = m->get_factors();
    ASSERT_EQ(3,factors.size());
    ASSERT_EQ(*x1,*factors.at(0));
    ASSERT_EQ(*x2,*factors.at(1));
    ASSERT_EQ(*x3,*factors.at(2));
}
