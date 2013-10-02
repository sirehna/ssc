/*
 * SplineVariableStepTest.cpp
 *
 * \date 9 sept. 2013, 10:46:50
 *  \author cec
 */

#include "SplineVariableStepTest.hpp"
#include "SplineVariableStep.hpp"
#include "IndexFinder.hpp"
#include "test_macros.hpp"

#define EPS 1E-10

SplineVariableStepTest::SplineVariableStepTest() : a(DataGenerator(7777777))
{
}

SplineVariableStepTest::~SplineVariableStepTest()
{
}

void SplineVariableStepTest::SetUp()
{
}

void SplineVariableStepTest::TearDown()
{
}

TEST_F(SplineVariableStepTest, example)
{
//! [SplineVariableStepTest example]
    SplineVariableStep S({1,0,20,2},{1,4,9,45});
//! [SplineVariableStepTest example]
//! [SplineVariableStepTest expected output]
    ASSERT_NEAR(1,S.f(1), EPS);
    ASSERT_NEAR(4,S.f(0), EPS);
    ASSERT_NEAR(9,S.f(20), EPS);
    ASSERT_NEAR(45,S.f(2), EPS);
//! [SplineVariableStepTest expected output]
}

TEST_F(SplineVariableStepTest, should_throw_if_vectors_are_not_the_same_length)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n1 = a.random<size_t>().between(1,1000);
        const size_t n2 = a.random<size_t>().between(1,1000).but_not(n1);
        const auto v1 = a.random_vector_of<double>().of_size(n1)();
        const auto v2 = a.random_vector_of<double>().of_size(n2)();
        ASSERT_THROW(SplineVariableStep(v1,v2),SplineVariableStepException);
    }
}

TEST_F(SplineVariableStepTest, should_throw_if_any_vector_is_empty)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const auto v = a.random_vector_of<double>()();
        const auto empty = std::vector<double>();
        ASSERT_THROW(SplineVariableStep(empty,v),SplineVariableStepException);
        ASSERT_THROW(SplineVariableStep(v,empty),SplineVariableStepException);
        ASSERT_THROW(SplineVariableStep(empty,empty),SplineVariableStepException);
    }
}

TEST_F(SplineVariableStepTest, should_throw_if_the_same_point_is_defined_twice)
{
    for (size_t n = 2 ; n < 100 ; ++n)
    {
        auto v = a.random_vector_of<double>().of_size(n)();
        const auto y = a.random_vector_of<double>().of_size(n)();
        const size_t i = a.random<size_t>().between(1,n-1);
        v[i] = v[i-1];
        ASSERT_THROW(SplineVariableStep(v,y), IndexFinderException);
    }
}

TEST_F(SplineVariableStepTest, should_throw_if_requesting_a_point_outside_bounds)
{
    std::cout.precision(20);
    for (size_t i = 0 ;i < 100 ; ++i)
    {
        const double a_ = a.random<double>();
        const double b_ = a.random<double>().greater_than(a_);
        const size_t n = a.random<size_t>().between(2,1000);
        auto v1 = a.random_vector_of<double>().between(a_,b_).of_size(n)();
        v1.front() = a_;
        v1.back() = b_;
        const auto v2 = a.random_vector_of<double>().of_size(n)();
        SplineVariableStep S(v1,v2);
        const double x_inside = a.random<double>().between(a_,b_);
        const double x_outside = a.random<double>().outside(a_,b_);
        ASSERT_THROW(S.f(x_outside),IndexFinderException);
        S.f(x_inside);
        ASSERT_NO_THROW(S.f(x_inside));
    }
}

TEST_F(SplineVariableStepTest, derivative_should_be_computed_properly)
{
    SplineVariableStep S({1,3,5,7,11,13},{1,3,5,7,11,13});
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        ASSERT_NEAR(1,S.df(a.random<double>().between(1,13)),EPS);
        ASSERT_NEAR(0,S.df(a.random<double>().between(1,13),2),EPS);
        ASSERT_NEAR(0,S.df(a.random<double>().between(1,13),3),EPS);
    }
    SplineVariableStep S2({1,3,5,7,11,13},{2,6,10,14,22,26});
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        ASSERT_NEAR(2,S2.df(a.random<double>().between(1,13)),EPS);
        ASSERT_NEAR(0,S2.df(a.random<double>().between(1,13),2),EPS);
        ASSERT_NEAR(0,S2.df(a.random<double>().between(1,13),3),EPS);
    }
}
