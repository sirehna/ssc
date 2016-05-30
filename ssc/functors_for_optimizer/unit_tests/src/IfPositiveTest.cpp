/*
 * AbsTest.cpp
 *
 *  Created on: Mar 3, 2016
 *      Author: cady
 */

#include <cmath>
#include "IfPositiveTest.hpp"
#include "ssc/functors_for_optimizer/Abs.hpp"

using namespace ssc::functors_for_optimizer;

#define X (*x)
#define X_ (x->get_lambda()())

IfPositiveTest::IfPositiveTest() : a(ssc::random_data_generator::DataGenerator(54515)), generate()
{
}

IfPositiveTest::~IfPositiveTest()
{
}

void IfPositiveTest::SetUp()
{
}

void IfPositiveTest::TearDown()
{
}

TEST_F(IfPositiveTest, example)
{
//! [IfPositiveTest example]
    auto x = generate.state("x");
    Abs s(x);
//! [IfPositiveTest example]
//! [IfPositiveTest expected output]
    auto abs_X = s.get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>();
        const double abs_x = std::abs((double)X_);
        ASSERT_DOUBLE_EQ(abs_x, abs_X());
    }
//! [AbsTest expected output]
}

TEST_F(IfPositiveTest, derivative)
{
    auto x = generate.state("x");
    Abs s(x);
    auto dabs_dx = s.diff(x)->get_lambda();

    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>();
        const double sign_x = X_ >= 0 ? 1 : -1;
        ASSERT_DOUBLE_EQ(sign_x, dabs_dx());
    }
}

TEST_F(IfPositiveTest, equality_operator)
{
    const auto x = generate.state("x");
    const auto y = generate.state("y");
    const Abs abs_x(x), abs_y(y);

    ASSERT_TRUE(abs_x.equals(abs_x));
    ASSERT_TRUE(abs_y.equals(abs_y));
    ASSERT_FALSE(abs_x.equals(abs_y));
    ASSERT_FALSE(abs_y.equals(abs_x));
}
