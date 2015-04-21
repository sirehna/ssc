/*
 * SinTest.cpp
 *
 * \date 1 f�vr. 2013, 14:20:08
 *  \author cec
 */

#include "CosTest.hpp"
#include "ssc/functors_for_optimizer/Cos.hpp"

using namespace ssc::functors_for_optimizer;

#define X (*x)
#define X_ (x->get_lambda()())

CosTest::CosTest() : a(ssc::random_data_generator::DataGenerator(1)), generate(StateGenerator())
{
}

CosTest::~CosTest()
{
}

void CosTest::SetUp()
{
}

void CosTest::TearDown()
{
}

TEST_F(CosTest, example)
{
//! [CosTest example]
    auto x = generate.state("x");
    Cos s(x);
//! [CosTest example]
//! [CosTest expected output]
    auto cos_X = s.get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>();
        ASSERT_DOUBLE_EQ(cos(X_), cos_X());
    }
//! [SinTest expected output]
}

TEST_F(CosTest, derivative)
{
    auto x = generate.state("x");
    Cos s(x);
    auto dcos_dx = s.diff(x)->get_lambda();

    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>();
        ASSERT_DOUBLE_EQ(-sin(X_), dcos_dx());
    }
}

TEST_F(CosTest, equality_operator)
{
    const auto x = generate.state("x");
    const auto y = generate.state("y");
    const Cos cos_x(x), cos_y(y);

    ASSERT_TRUE(cos_x.equals(cos_x));
    ASSERT_TRUE(cos_y.equals(cos_y));
    ASSERT_FALSE(cos_x.equals(cos_y));
    ASSERT_FALSE(cos_y.equals(cos_x));
}
