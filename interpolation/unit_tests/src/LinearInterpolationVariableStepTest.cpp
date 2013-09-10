/*
 * LinearInterpolationVariableStepTest.cpp
 *
 * \date 10 avr. 2013, 12:52:58
 *  \author cec
 */

#include "LinearInterpolationVariableStepTest.hpp"
#include "LinearInterpolationVariableStep.hpp"
#include "PiecewiseConstantVariableStep.hpp"
#include "InterpolatorException.hpp"
#include "random_increasing_vector.hpp"
#include "extra_test_assertions.hpp"
#include "IndexFinder.hpp"

#define EPS 1e-4


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
//! [LinearInterpolationVariableStepTest example]
//! [LinearInterpolationVariableStepTest expected output]
    ASSERT_DOUBLE_EQ(2, interpolate.f(2));
    ASSERT_DOUBLE_EQ(2, interpolate.f(5));
    ASSERT_DOUBLE_EQ(5, interpolate.f(7));
    ASSERT_DOUBLE_EQ(4, interpolate.f(7.5));
    ASSERT_DOUBLE_EQ(8, interpolate.f(11));
    ASSERT_DOUBLE_EQ(7, interpolate.f(13));

//! [LinearInterpolationVariableStepTest expected output]
}
TEST_F(LinearInterpolationVariableStepTest, should_be_able_to_retrieve_initial_values)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        LinearInterpolationVariableStep interpolate(x,y);
        for (size_t i = 0 ; i < n ; ++i)
        {
            ASSERT_SMALL_RELATIVE_ERROR(y.at(i), interpolate.f(x.at(i)),EPS);
        }
    }
}

TEST_F(LinearInterpolationVariableStepTest, first_derivative_should_be_zero_if_y_is_constant)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y(n, a.random<double>());
        LinearInterpolationVariableStep interpolate(x,y);
        for (size_t i = 0 ; i < n ; ++i)
        {
            //COUT("");
            ASSERT_DOUBLE_EQ(0, interpolate.df(a.random<double>().between(x.front(),x.back())));
//            COUT("");
        }
    }
}

TEST_F(LinearInterpolationVariableStepTest, first_derivative_should_be_constant_if_points_are_on_straight_line)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const double slope = a.random<double>();
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        std::vector<double> y;
        const double x0 = x.front();
        for (auto it = x.begin() ; it != x.end() ; ++it)
        {
            y.push_back(slope*(*it-x0));
        }
        LinearInterpolationVariableStep interpolate(x,y);
        for (size_t i = 0 ; i < n ; ++i)
        {
            ASSERT_SMALL_RELATIVE_ERROR(slope, interpolate.df(a.random<double>().between(x.front(),x.back())),EPS);
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
        ASSERT_DOUBLE_EQ(0,interpolate.df(a.random<double>().between(2,5)));
        ASSERT_DOUBLE_EQ(1.5,interpolate.df(a.random<double>().between(5,7)));
        ASSERT_DOUBLE_EQ(-2,interpolate.df(a.random<double>().between(7,7.5)));
        ASSERT_DOUBLE_EQ(4./3.5,interpolate.df(a.random<double>().between(7.5,11)));
        ASSERT_DOUBLE_EQ(-0.5,interpolate.df(a.random<double>().between(11,13)));
    }
}

TEST_F(LinearInterpolationVariableStepTest, second_derivative_should_always_be_zero)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        LinearInterpolationVariableStep interpolate(x,y);
        for (size_t i = 0 ; i < 20 ; ++i)
        {
            ASSERT_DOUBLE_EQ(0, interpolate.df(a.random<double>().between(x.front(),x.back()),2));
        }
    }
}

TEST_F(LinearInterpolationVariableStepTest, interpolated_values_should_be_between_bounds)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        LinearInterpolationVariableStep interpolate(x,y);
        for (size_t i = 0 ; i < n-1 ; ++i)
        {
            const double y0 = y.at(i)>y.at(i+1) ? y.at(i+1) : y.at(i);
            const double y1 = y.at(i)>y.at(i+1) ? y.at(i) : y.at(i+1);
            ASSERT_LE(y0, interpolate.f(a.random<double>().between(x.at(i),x.at(i+1))));
            ASSERT_GE(y1, interpolate.f(a.random<double>().between(x.at(i),x.at(i+1))));
        }
    }
}

TEST_F(LinearInterpolationVariableStepTest, should_throw_if_x_and_y_have_different_sizes)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const size_t different_n = a.random<size_t>().between(2,100).but_not(n);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(different_n);
        ASSERT_THROW(LinearInterpolationVariableStep(x,y), PiecewiseConstantVariableStepException);
    }
}

TEST_F(LinearInterpolationVariableStepTest, should_throw_if_x_is_not_in_strictly_increasing_order)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        ASSERT_NO_THROW(LinearInterpolationVariableStep(x,y));
        const size_t idx = a.random<size_t>().between(1,n-1);
        x.at(idx) = x.at(idx-1);
        ASSERT_THROW(LinearInterpolationVariableStep(x,y), IndexFinderException);
        x.at(idx) = x.at(idx-1)-1;
        ASSERT_THROW(LinearInterpolationVariableStep(x,y), IndexFinderException);
    }
}

TEST_F(LinearInterpolationVariableStepTest, should_throw_if_there_are_not_at_least_two_points)
{
    ASSERT_THROW(LinearInterpolationVariableStep(std::vector<double>(),std::vector<double>()), InterpolatorException);
    ASSERT_THROW(LinearInterpolationVariableStep(std::vector<double>(1,a.random<double>()),std::vector<double>(1,a.random<double>())), PiecewiseConstantVariableStepException);
}

TEST_F(LinearInterpolationVariableStepTest, should_throw_if_retrieving_an_x_outside_bounds)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        LinearInterpolationVariableStep interpolate(x,y);
        ASSERT_THROW(interpolate.f(a.random<double>().outside(x.front(),x.back())), IndexFinderException);
        ASSERT_THROW(interpolate.df(a.random<double>().outside(x.front(),x.back())), IndexFinderException);
        ASSERT_THROW(interpolate.df(a.random<double>().outside(x.front(),x.back()),2), IndexFinderException);
    }
}
