/*
 * SumTest.cpp
 *
 * \date 31 janv. 2013, 16:02:15
 *  \author cec
 */

#include "SumTest.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"
#include "ssc/functors_for_optimizer/Sum.hpp"
#include "ssc/functors_for_optimizer/Constant.hpp"
#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"
#include "ssc/functors_for_optimizer/Serialize.hpp"

SumTest::SumTest() : a(ssc::random_data_generator::DataGenerator(12)), generate(StateGenerator())
{
}

SumTest::~SumTest()
{
}

void SumTest::SetUp()
{
}

void SumTest::TearDown()
{
}

TEST_F(SumTest, example)
{
//! [SumTest example]
    StateGenerator generate;
    auto x = generate.state("x");
    auto y = generate.state("y");
    Sum s(x,y);
//! [SumTest example]
//! [SumTest expected output]
    for (size_t i = 0 ; i<1000 ; ++i)
    {
        const double v1 = a.random<double>();
        const double v2 = a.random<double>();
        *x = v1;
        *y = v2;
        ASSERT_DOUBLE_EQ(v1+v2,s.get_lambda()());
    }
//! [SumTest expected output]
}

TEST_F(SumTest, derivative)
{
    StateGenerator generate;
    auto x = generate.state("x");
    auto y = generate.state("y");
    Sum s(x,y);
    ASSERT_EQ(1,s.diff(x)->get_lambda()());
    ASSERT_EQ(1,s.diff(y)->get_lambda()());
}

TEST_F(SumTest, comparison_to_constant_bug)
{
    ConstantPtr c(new Constant(1));
    std::vector<NodePtr> nodes(1,c);
    SumPtr one(new Sum(nodes));
    ASSERT_EQ(1, one);
}

TEST_F(SumTest, should_be_able_to_get_the_operands_in_a_sum_of_two)
{
    StateGenerator generate;
    auto x = generate.state("x");
    auto y = generate.state("y");
    SumPtr s(new Sum(x,y));
    auto operands = s->get_operands();
    ASSERT_EQ(2,operands.size());
    ASSERT_EQ(*x,*operands.at(0));
    ASSERT_EQ(*y,*operands.at(1));
}

TEST_F(SumTest, should_be_able_to_get_the_operands_in_a_sum_of_three)
{
    StateGenerator generate;
    auto x = generate.state("x");
    auto y = generate.state("y");
    auto z = generate.state("z");
    auto s = x+y+z;
    auto operands = s->get_operands();
    ASSERT_EQ(3,operands.size());
    ASSERT_EQ(*x,*operands.at(0));
    ASSERT_EQ(*y,*operands.at(1));
    ASSERT_EQ(*z,*operands.at(2));
}

