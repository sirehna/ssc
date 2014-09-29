/*
 * AngleTest.cpp
 *
 * \date 14 mars 2013, 10:45:43
 *  \author cec
 */

#define _USE_MATH_DEFINES
#include <cmath>
#ifndef M_PI
#define M_PI (4*atan(1.))
#endif
#define PI M_PI

#include "AngleTest.hpp"
#include "ssc/geometry/Angle.hpp"
#include "ssc/macros/extra_test_assertions.hpp"

#define EPS 1E-6

using namespace ssc::geometry;

AngleTest::AngleTest() : a(ssc::random_data_generator::DataGenerator(88))
{
}

AngleTest::~AngleTest()
{
}

void AngleTest::SetUp()
{
}

void AngleTest::TearDown()
{
}

TEST_F(AngleTest, example)
{
//! [AngleTest example]
    const Angle ninety_degrees = Angle::degree(90);
    const Angle thirty_degrees = Angle::degree(30);
    const Angle sixty_degrees=thirty_degrees*2;
    const Angle twenty_degrees=sixty_degrees/3;
    const Angle eighty_degrees = Angle::degree(80);
    const Angle dms = Angle::degree_minute_second(5,20,30);
    const Angle dmsneg = -dms;
//! [AngleTest example]
//! [AngleTest expected output]
    ASSERT_SMALL_RELATIVE_ERROR(0, cos(ninety_degrees), EPS);
    ASSERT_SMALL_RELATIVE_ERROR(1, sin(ninety_degrees), EPS);
    ASSERT_SMALL_RELATIVE_ERROR(cos(thirty_degrees), std::sqrt(3.0)/2.0, EPS);
    ASSERT_SMALL_RELATIVE_ERROR(sin(thirty_degrees), 0.5, EPS);
    ASSERT_SMALL_RELATIVE_ERROR(60, Angle::degree(60).get_degree(), EPS);
    ASSERT_SMALL_RELATIVE_ERROR(60, sixty_degrees.get_degree(), EPS);
    ASSERT_SMALL_RELATIVE_ERROR(twenty_degrees.get_degree(), 20, EPS);
    ASSERT_EQ(eighty_degrees, sixty_degrees+twenty_degrees);
    ASSERT_SMALL_RELATIVE_ERROR(0,(dmsneg + dms).get_degree(), EPS);
//! [AngleTest expected output]
}

TEST_F(AngleTest, should_be_able_to_multiply_an_angle_by_a_constant)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double value_in_degrees = a.random<double>();
        const double value_in_radians = a.random<double>();
        const double constant = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR(value_in_degrees*constant, (Angle::degree(value_in_degrees)*constant).get_degree(), EPS);
        ASSERT_SMALL_RELATIVE_ERROR(constant*value_in_degrees, (Angle::degree(value_in_degrees)*constant).get_degree(), EPS);
        ASSERT_SMALL_RELATIVE_ERROR(value_in_radians*constant, (Angle::radian(value_in_radians)*constant).get_radian(), EPS);
        ASSERT_SMALL_RELATIVE_ERROR(constant*value_in_radians, (Angle::radian(value_in_radians)*constant).get_radian(), EPS);
    }
}

TEST_F(AngleTest, should_be_able_to_divide_an_angle_by_a_constant)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double value_in_degrees = a.random<double>();
        const double value_in_radians = a.random<double>();
        const double constant = a.random<double>().outside(-EPS,EPS);
        ASSERT_SMALL_RELATIVE_ERROR(value_in_degrees/constant, (Angle::degree(value_in_degrees)/constant).get_degree(), EPS);
        ASSERT_SMALL_RELATIVE_ERROR(value_in_radians/constant, (Angle::radian(value_in_radians)/constant).get_radian(), EPS);
    }
}

TEST_F(AngleTest, should_be_able_to_negate_an_angle)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double value_in_radians = a.random<double>();
        const double value_in_degrees = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR(-value_in_degrees,(-Angle::degree(value_in_degrees)).get_degree(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(-value_in_radians,(-Angle::radian(value_in_radians)).get_radian(),EPS);
    }
}

TEST_F(AngleTest, should_be_able_to_compare_two_angles)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double value1_in_radians = a.random<double>();
        const double value1_in_degrees = a.random<double>();
        const double value2_in_radians = a.random<double>().but_not(value1_in_radians);
        const double value2_in_degrees = a.random<double>().but_not(value1_in_degrees);
        ASSERT_EQ(Angle::degree(value1_in_degrees),Angle::degree(value1_in_degrees));
        ASSERT_NE(Angle::degree(value1_in_degrees),Angle::degree(value2_in_degrees));
        ASSERT_EQ(Angle::degree(value1_in_radians),Angle::degree(value1_in_radians));
        ASSERT_NE(Angle::degree(value1_in_radians),Angle::degree(value2_in_radians));
    }
}

TEST_F(AngleTest, should_be_able_to_add_two_angles)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double value1_in_radians = a.random<double>();
        const double value1_in_degrees = a.random<double>();
        const double value2_in_radians = a.random<double>();
        const double value2_in_degrees = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR(value1_in_radians+value2_in_radians,(Angle::radian(value1_in_radians)+Angle::radian(value2_in_radians)).get_radian(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(value1_in_degrees+value2_in_degrees,(Angle::degree(value1_in_degrees)+Angle::degree(value2_in_degrees)).get_degree(),EPS);
    }
}

TEST_F(AngleTest, should_be_able_to_substract_two_angles)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double value1_in_radians = a.random<double>();
        const double value1_in_degrees = a.random<double>();
        const double value2_in_radians = a.random<double>();
        const double value2_in_degrees = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR(value1_in_radians-value2_in_radians,(Angle::radian(value1_in_radians)-Angle::radian(value2_in_radians)).get_radian(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(value1_in_degrees-value2_in_degrees,(Angle::degree(value1_in_degrees)-Angle::degree(value2_in_degrees)).get_degree(),EPS);
    }
}

TEST_F(AngleTest, should_be_able_to_retrieve_the_value_in_degrees)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double value_in_radians = a.random<double>();
        const double value_in_degrees = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR(value_in_degrees, Angle::degree(value_in_degrees).get_degree(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(value_in_radians*180./PI, Angle::radian(value_in_radians).get_degree(),EPS);
    }
}

TEST_F(AngleTest, should_be_able_to_retrieve_the_value_in_radians)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double value_in_radians = a.random<double>();
        const double value_in_degrees = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR(value_in_radians, Angle::radian(value_in_radians).get_radian(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(value_in_degrees*PI/180., Angle::degree(value_in_degrees).get_radian(),EPS);
    }
}

TEST_F(AngleTest, should_be_able_to_calculate_the_cosine_of_an_angle)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double value_in_radians = a.random<double>();
        const double value_in_degrees = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR(cos(value_in_radians), cos(Angle::radian(value_in_radians)), EPS);
        ASSERT_SMALL_RELATIVE_ERROR(cos(value_in_degrees*PI/180.), cos(Angle::degree(value_in_degrees)), EPS);
    }
}

TEST_F(AngleTest, should_be_able_to_calculate_the_sine_of_an_angle)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double value_in_radians = a.random<double>();
        const double value_in_degrees = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR(sin(value_in_radians), sin(Angle::radian(value_in_radians)), EPS);
        ASSERT_SMALL_RELATIVE_ERROR(sin(value_in_degrees*PI/180.), sin(Angle::degree(value_in_degrees)), EPS);
    }
}

TEST_F(AngleTest, should_be_able_to_calculate_the_tangent_of_an_angle)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double value_in_radians = a.random<double>();
        const double value_in_degrees = a.random<double>().between(-1E7,1E7);
        ASSERT_SMALL_RELATIVE_ERROR(tan(value_in_radians), tan(Angle::radian(value_in_radians)), EPS);
        ASSERT_SMALL_RELATIVE_ERROR(tan(value_in_degrees*PI/180.), tan(Angle::degree(value_in_degrees)), EPS);
    }
}

