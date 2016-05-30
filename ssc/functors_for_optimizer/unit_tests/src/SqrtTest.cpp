/*
 * SqrtTest.cpp
 *
 *  Created on: Mar 8, 2016
 *      Author: cady
 */

#include <cmath>

#include "SqrtTest.hpp"
#include "ssc/functors_for_optimizer/Sqrt.hpp"

using namespace ssc::functors_for_optimizer;

#define X (*x)
#define X_ (x->get_lambda()())


SqrtTest::SqrtTest() : a(ssc::random_data_generator::DataGenerator(85412121)), generate(StateGenerator())
{
}

SqrtTest::~SqrtTest()
{
}

void SqrtTest::SetUp()
{
}

void SqrtTest::TearDown()
{
}

TEST_F(SqrtTest, example)
{
    auto x = generate.state("x");
    Sqrt s(x);
    auto sqrt_X = s.get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().greater_than(0);
        ASSERT_DOUBLE_EQ(std::sqrt(X_), sqrt_X());
    }
}

TEST_F(SqrtTest, derivative)
{
    auto x = generate.state("x");
    Sqrt s(x);
    auto dsqrt_dx = s.diff(x)->get_lambda();

    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().greater_than(0);
        ASSERT_DOUBLE_EQ(1./(2*std::sqrt(X_)), dsqrt_dx());
    }
}

TEST_F(SqrtTest, equality_operator)
{
    const auto x = generate.state("x");
    const auto y = generate.state("y");
    const Sqrt sqrt_x(x), sqrt_y(y);

    ASSERT_TRUE(sqrt_x.equals(sqrt_x));
    ASSERT_TRUE(sqrt_y.equals(sqrt_y));
    ASSERT_FALSE(sqrt_x.equals(sqrt_y));
    ASSERT_FALSE(sqrt_y.equals(sqrt_x));
}




