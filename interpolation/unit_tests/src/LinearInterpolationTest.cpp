/*
 * LinearInterpolationTest.cpp
 *
 * \date 8 nov. 2012, 14:31:52
 *  \author cec
 */

#include "LinearInterpolationTest.hpp"
#include "test_macros.hpp"
#include "LinearInterpolation.hpp"

LinearInterpolationTest::LinearInterpolationTest() : a(DataGenerator(23))
{
}

LinearInterpolationTest::~LinearInterpolationTest()
{
}

void LinearInterpolationTest::SetUp()
{
}

void LinearInterpolationTest::TearDown()
{
}

TEST_F(LinearInterpolationTest, example)
{
//! [LinearInterpolationTest example]
    LinearInterpolation interpolate(0,10,{0,1,2,3,4,5,6,7,8,9,10});
//! [LinearInterpolationTest example]
//! [LinearInterpolationTest expected output]
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double val = a.random<double>().between(0,10);
        interpolate.set_computed_value(val);
        ASSERT_DOUBLE_EQ(val, interpolate.f());
    }
//! [LinearInterpolationTest expected output]
}

TEST_F(LinearInterpolationTest, f_should_work_properly)
{
    LinearInterpolation interpolate(0,10,{10,0});
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double val = a.random<double>().between(0,10);
        interpolate.set_computed_value(val);
        ASSERT_DOUBLE_EQ(10-val, interpolate.f());
    }
}

TEST_F(LinearInterpolationTest, df_should_work_properly)
{
    LinearInterpolation interpolate(0,10,{10,0});
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double val = a.random<double>().between(0,10);
        interpolate.set_computed_value(val);
        ASSERT_DOUBLE_EQ(-1, interpolate.df());
    }
}

TEST_F(LinearInterpolationTest, d2f_should_work_properly)
{
    const size_t n = a.random<size_t>().no().greater_than(30);
    LinearInterpolation interpolate(0,10,a.random_vector_of<double>().of_size(n));
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double val = a.random<double>();
        interpolate.set_computed_value(val);
        ASSERT_EQ(0, interpolate.d2f());
    }
}
