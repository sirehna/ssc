/*
 * SplineFunctorTest.cpp
 *
 * \date 18 févr. 2013, 12:46:48
 *  \author cec
 */

#include "SplineFunctorTest.hpp"


#include "test_macros.hpp"

SplineFunctorTest::SplineFunctorTest() : a(DataGenerator(23))
{
}

SplineFunctorTest::~SplineFunctorTest()
{
}

void SplineFunctorTest::SetUp()
{
}

void SplineFunctorTest::TearDown()
{
}

TEST_F(SplineFunctorTest, example)
{
//! [SplineFunctorTest example]
//! [SplineFunctorTest example]
//! [SplineFunctorTest expected output]
//! [SplineFunctorTest expected output]
}

TEST_F(SplineFunctorTest, third_derivative_of_cubic_spline_should_be_zero)
{

}

TEST_F(SplineFunctorTest, second_derivative_of_cubic_spline_should_be_piecewise_constant)
{

}

TEST_F(SplineFunctorTest, first_derivative_of_cubic_spline_should_be_computed_correctly)
{

}

TEST_F(SplineFunctorTest, value_of_spline_should_be_computed_correctly)
{

}
