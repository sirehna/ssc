/*
 * LinearInterpolationVariableStepTest.cpp
 *
 * \date 10 avr. 2013, 12:52:58
 *  \author cec
 */

#include "LinearInterpolationVariableStepTest.hpp"
#include "LinearInterpolationVariableStep.hpp"
#include "extra_test_assertions.hpp"

#define EPS 1e-10

LinearInterpolationVariableStepTest::LinearInterpolationVariableStepTest() : a(DataGenerator(12))
{
}

LinearInterpolationVariableStepTest::~LinearInterpolationVariableStepTest()
{
}

void LinearInterpolationVariableStepTest::SetUp()
{
}

void LinearInterpolationVariableStepTest::TearDown()
{
}

TEST_F(LinearInterpolationVariableStepTest, example)
{
//! [LinearInterpolationVariableStepTest example]
    const std::vector<double> x = {2,5,7,7.5,11,13};
    const std::vector<double> y = {2,2,5,4  ,8 ,7};
    LinearInterpolationVariableStep interpolate(x,y);
    interpolate.set_computed_value(7.5);
//! [LinearInterpolationVariableStepTest example]
//! [LinearInterpolationVariableStepTest expected output]
    ASSERT_DOUBLE_EQ(4, interpolate.f());
//! [LinearInterpolationVariableStepTest expected output]
}

std::vector<double> LinearInterpolationVariableStepTest::a_random_vector_of_doubles_in_increasing_order_of_size(const size_t& n) const
{
    std::vector<double> ret;
    if (n) ret.push_back(a.random<double>());
    for (size_t i = 1 ; i < n ; ++i)
    {
        const double step = a.random<double>().between(0,1000);
        ret.push_back(ret.back()+step);
    }
    return ret;
}

TEST_F(LinearInterpolationVariableStepTest, should_be_able_to_retrieve_initial_values)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        LinearInterpolationVariableStep interpolate(x,y);
        for (size_t i = 0 ; i < n ; ++i)
        {
            interpolate.set_computed_value(x.at(i));
            ASSERT_DOUBLE_EQ(y.at(i), interpolate.f());
        }
    }
}

TEST_F(LinearInterpolationVariableStepTest, first_derivative_should_be_zero_if_y_is_constant)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(n);
        const std::vector<double> y(n, a.random<double>());
        LinearInterpolationVariableStep interpolate(x,y);
        for (size_t i = 0 ; i < n ; ++i)
        {
            x.front();
            x.back();
            interpolate.set_computed_value(a.random<double>().between(x.front(),x.back()));
            ASSERT_DOUBLE_EQ(0, interpolate.df());
        }
    }
}

TEST_F(LinearInterpolationVariableStepTest, first_derivative_should_be_constant_if_points_are_on_straight_line)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const double slope = a.random<double>();
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(n);
        std::vector<double> y;
        const double x0 = x.front();
        for (auto it = x.begin() ; it != x.end() ; ++it)
        {
            y.push_back(slope*(*it-x0));
        }
        LinearInterpolationVariableStep interpolate(x,y);
        for (size_t i = 0 ; i < n ; ++i)
        {
            interpolate.set_computed_value(a.random<double>().between(x.front(),x.back()));
            ASSERT_SMALL_RELATIVE_ERROR(slope, interpolate.df(),EPS);
        }
    }
}

TEST_F(LinearInterpolationVariableStepTest, first_derivative_should_be_correctly_computed_for_example_case)
{
    const std::vector<double> x = {2,5,7,7.5,11,13};
    const std::vector<double> y = {2,2,5,4  ,8 ,7};
    LinearInterpolationVariableStep interpolate(x,y);
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        interpolate.set_computed_value(a.random<double>().between(2,5));
        ASSERT_DOUBLE_EQ(0,interpolate.df());
        interpolate.set_computed_value(a.random<double>().between(5,7));
        ASSERT_DOUBLE_EQ(1.5,interpolate.df());
        interpolate.set_computed_value(a.random<double>().between(7,7.5));
        ASSERT_DOUBLE_EQ(-2,interpolate.df());
        interpolate.set_computed_value(a.random<double>().between(7.5,11));
        ASSERT_DOUBLE_EQ(4./3.5,interpolate.df());
        interpolate.set_computed_value(a.random<double>().between(11,13));
        ASSERT_DOUBLE_EQ(-0.5,interpolate.df());
    }
}

TEST_F(LinearInterpolationVariableStepTest, second_derivative_should_always_be_zero)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        LinearInterpolationVariableStep interpolate(x,y);
        for (size_t i = 0 ; i < 20 ; ++i)
        {
            interpolate.set_computed_value(a.random<double>().between(x.front(),x.back()));
            ASSERT_DOUBLE_EQ(0, interpolate.d2f());
        }
    }
}

TEST_F(LinearInterpolationVariableStepTest, interpolated_values_should_be_between_bounds)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        LinearInterpolationVariableStep interpolate(x,y);
        for (size_t i = 0 ; i < n-1 ; ++i)
        {
            interpolate.set_computed_value(a.random<double>().between(x.at(i),x.at(i+1)));
            const double y0 = y.at(i)>y.at(i+1) ? y.at(i+1) : y.at(i);
            const double y1 = y.at(i)>y.at(i+1) ? y.at(i) : y.at(i+1);
            ASSERT_LE(y0, interpolate.f());
            ASSERT_GE(y1, interpolate.f());
        }
    }
}

TEST_F(LinearInterpolationVariableStepTest, should_throw_if_x_and_y_have_different_sizes)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const size_t different_n = a.random<size_t>().between(2,100).but_not(n);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(different_n);
        ASSERT_THROW(LinearInterpolationVariableStep(x,y), LinearInterpolationVariableStepException);
    }
}

TEST_F(LinearInterpolationVariableStepTest, should_throw_if_x_is_not_in_strictly_increasing_order)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        ASSERT_NO_THROW(LinearInterpolationVariableStep(x,y));
        const size_t idx = a.random<size_t>().between(1,n-1);
        x.at(idx) = x.at(idx-1);
        ASSERT_THROW(LinearInterpolationVariableStep(x,y), LinearInterpolationVariableStepException);
        x.at(idx) = x.at(idx-1)-1;
        ASSERT_THROW(LinearInterpolationVariableStep(x,y), LinearInterpolationVariableStepException);
    }
}

TEST_F(LinearInterpolationVariableStepTest, should_throw_if_there_are_not_at_least_two_points)
{
    ASSERT_THROW(LinearInterpolationVariableStep(std::vector<double>(),std::vector<double>()), LinearInterpolationVariableStepException);
    ASSERT_THROW(LinearInterpolationVariableStep(std::vector<double>(1,a.random<double>()),std::vector<double>(1,a.random<double>())), LinearInterpolationVariableStepException);
}

TEST_F(LinearInterpolationVariableStepTest, should_throw_if_retrieving_an_x_outside_bounds)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        LinearInterpolationVariableStep interpolate(x,y);
        ASSERT_THROW(interpolate.set_computed_value(a.random<double>().outside(x.front(),x.back())), LinearInterpolationVariableStepException);
    }
}
