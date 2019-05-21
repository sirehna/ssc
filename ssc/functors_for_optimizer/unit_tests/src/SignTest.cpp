/*
 * SignTest.cpp
 *
 * \date Mar 3, 2016
 * \author cec
 */


#include "SignTest.hpp"
#include "ssc/functors_for_optimizer/Sign.hpp"

using namespace ssc::functors_for_optimizer;

#define X (*x)
#define X_ (x->get_lambda()())

SignTest::SignTest() : a(ssc::random_data_generator::DataGenerator(87451)), generate(StateGenerator())
{
}

SignTest::~SignTest()
{
}

void SignTest::SetUp()
{
}

void SignTest::TearDown()
{
}

TEST_F(SignTest, example)
{
//! [SignTest example]
    auto x = generate.state("x");
    Sign s(x);
//! [SignTest example]
//! [SignTest expected output]
    auto sign_X = s.get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>();
        if (X_ >= 0) ASSERT_EQ(1, sign_X());
        else         ASSERT_EQ(-1, sign_X());
    }
//! [SignTest expected output]
}

TEST_F(SignTest, derivative)
{
    auto x = generate.state("x");
    Sign s(x);
    auto dsign_dx = s.diff(x)->get_lambda();

    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>();
        ASSERT_DOUBLE_EQ(0, dsign_dx());
    }
}

TEST_F(SignTest, equality_operator)
{
    const auto x = generate.state("x");
    const auto y = generate.state("y");
    const Sign sign_x(x), sign_y(y);

    ASSERT_TRUE(sign_x.equals(sign_x));
    ASSERT_TRUE(sign_y.equals(sign_y));
    ASSERT_FALSE(sign_x.equals(sign_y));
    ASSERT_FALSE(sign_y.equals(sign_x));
}
