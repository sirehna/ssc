/*
 * SinTest.cpp
 *
 * \date 1 févr. 2013, 14:20:08
 *  \author cec
 */

#include "SinTest.hpp"
#include "Sin.hpp"

#define PI 4.*(atan(1.))


#define X (*x)
#define X_ (x->get_lambda()())

SinTest::SinTest() : a(DataGenerator(1)), generate(StateGenerator())
{
}

SinTest::~SinTest()
{
}

void SinTest::SetUp()
{
}

void SinTest::TearDown()
{
}

TEST_F(SinTest, example)
{
//! [SinTest example]
    auto x = generate.state("x");
    Sin s(x);
//! [SinTest example]
//! [SinTest expected output]
    auto sin_X = s.get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>();
        ASSERT_DOUBLE_EQ(sin(X_), sin_X());
    }
//! [SinTest expected output]
}

TEST_F(SinTest, derivative)
{
    auto x = generate.state("x");
    Sin s(x);
    auto dsinX_dX = s.diff(x)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>();
        ASSERT_DOUBLE_EQ(cos(X_), dsinX_dX());
    }
}


