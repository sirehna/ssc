/*
 * SplineTest.cpp
 *
 * \date 8 juin 2012, 17:07:12
 *  \author cec
 */

#include <cmath>
#include <algorithm>

#include "SplinesTest.hpp"
#include "extra_test_assertions.hpp"
#include "NaturalSplines.hpp"
#include "VectorOfEquallySpacedNumbers.hpp"
#include "VectorOfEquallySpacedNumbersException.hpp"
#include "InterpolatorException.hpp"
#include "SplinesException.hpp"

#define PI 4.*atan(1.)
#define EPS 1E-10

template<> VectorOfEquallySpacedNumbers get_min_bound<VectorOfEquallySpacedNumbers>();
template<> VectorOfEquallySpacedNumbers get_max_bound<VectorOfEquallySpacedNumbers>();


SplinesTest::SplinesTest() : a(DataGenerator(316497))
{
}

SplinesTest::~SplinesTest()
{
}

void SplinesTest::SetUp()
{
}

void SplinesTest::TearDown()
{
}

TEST_F(SplinesTest, example)
{
//! [SplineTest example]
	const std::vector<double> y = {0,9,36,81};
	NaturalSplines spline(0,9,y);
//! [SplineTest example]
//! [SplineTest expected output]
	ASSERT_DOUBLE_EQ(9,spline.f(3));
	ASSERT_DOUBLE_EQ(5.4,spline.df(3));
	ASSERT_DOUBLE_EQ(2.4,spline.df(3,2));
//! [SplineTest expected output]
}

TEST_F(SplinesTest, value_at_the_interpolation_points_should_be_the_same_as_that_given_in_the_input_data)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const VectorOfEquallySpacedNumbers x(0,6,70);
        const std::vector<double> y = a.random_vector_of<double>().of_size(x.size());
        NaturalSplines spline(x.get_min(),x.get_max(),y);
        for (size_t j = 0 ; j < x.size() ; ++j)
        {
            ASSERT_SMALL_RELATIVE_ERROR(y.at(j), spline.f(x.at(j)),EPS);
        }
    }
}

TEST_F(SplinesTest, interpolated_value_should_lie_between_the_value_of_the_spline_at_the_surrounding_knots)
{
	const VectorOfEquallySpacedNumbers x(10,16,7);
	const std::vector<double> y = {12,23,34,45,56,67,78};
	NaturalSplines spline(x.get_min(),x.get_max(),y);
	for (size_t i = 0 ; i < x.size()-1 ; ++i)
	{
		const double x0 = a.random<double>().between(x.at(i),x.at(i+1));
		const double lower_bound = std::min(y.at(i),y.at(i+1));
		const double upper_bound = std::max(y.at(i),y.at(i+1));
		ASSERT_GE(spline.f(x0),lower_bound);
		ASSERT_LE(spline.f(x0),upper_bound);
	}
}

TEST_F(SplinesTest, constructor_should_throw_an_exception_if_there_are_fewer_than_two_points_and_xmin_doesnt_equal_xmax)
{
	const std::vector<double> an_empty_vector = std::vector<double>();
	const std::vector<double> a_vector_with_one_element = a.random_vector_of<double>().of_size(1);
	ASSERT_THROW(NaturalSplines(0, 1,an_empty_vector),InterpolatorException);
	ASSERT_THROW(NaturalSplines(0, 1,a_vector_with_one_element),VectorOfEquallySpacedNumbersException);
	NaturalSplines(0, 0,a_vector_with_one_element);
}

TEST_F(SplinesTest, should_be_able_to_build_an_empty_spline)
{
	NaturalSplines s;
	ASSERT_EQ(0, s.f(a.random<double>()));
	ASSERT_EQ(0, s.df(a.random<double>()));
	ASSERT_EQ(0, s.df(a.random<double>(),2));
}

TEST_F(SplinesTest, should_be_able_to_assign_a_spline)
{
	const std::vector<double> y = {0,9,36,81};
	NaturalSplines spline(0,9,y);
	ASSERT_EQ(9,spline.f(3));
	NaturalSplines empty;
	spline = empty;
	ASSERT_EQ(0,spline.f(a.random<double>()));
}

TEST_F(SplinesTest, bug1_index_is_incorrect_when_value_is_much_greater_than_max_bound)
{
	const std::vector<double> y = {0,9,36,81};
	NaturalSplines spline(0,4,y);
	ASSERT_NO_THROW(spline.f(a.random<double>().greater_than(123456789)));
}

TEST_F(SplinesTest, bug1_index_is_incorrect_when_value_is_much_lower_than_min_bound)
{
	const std::vector<double> y = {0,9,36,81};
	NaturalSplines spline(0,4,y);
	ASSERT_NO_THROW(spline.f(a.random<double>().no().greater_than(-123456789)));
}

TEST_F(SplinesTest, bug_2_range_check_exception_with_certain_inputs)
{
    const std::vector<double> y = {1.0000,0.9397,0.7660,0.5000,0.1736,-0.1736,-0.5000,-0.7660,-0.9397,-1.0000};
    const double x0 = -1e-16;
    const double xmin = -PI;
    const double xmax = 0;
    NaturalSplines spline(xmin, xmax,y);

    ASSERT_NO_THROW(spline.f(x0));
    ASSERT_NO_THROW(spline.df(x0));
    ASSERT_NO_THROW(spline.df(x0,2));
}

TEST_F(SplinesTest, should_be_able_to_retrieve_parabolic_coefficients)
{
    NaturalSplines s(0,3,{0,1,4,3});
    ASSERT_DOUBLE_EQ(0,s.f(0));
    ASSERT_DOUBLE_EQ(0.6250000000e-1,s.f(0.25));
    ASSERT_DOUBLE_EQ(0.2,s.f(0.5));
    ASSERT_DOUBLE_EQ(.4875000000,s.f(0.75));
    ASSERT_DOUBLE_EQ(1,s.f(1));
    ASSERT_DOUBLE_EQ(1.768750000,s.f(1.25));
    ASSERT_DOUBLE_EQ(2.65,s.f(1.5));
    ASSERT_DOUBLE_EQ(3.45625000,s.f(1.75));
    ASSERT_DOUBLE_EQ(4,s.f(2));
    ASSERT_DOUBLE_EQ(4.14375000,s.f(2.25));
    ASSERT_DOUBLE_EQ(3.95,s.f(2.5));
    ASSERT_DOUBLE_EQ(3.53125000,s.f(2.75));
    ASSERT_DOUBLE_EQ(3,s.f(3));



    auto coeffs2 = s.get_parabolic_coefficients();



    ASSERT_EQ(3, coeffs2.size());
    ASSERT_DOUBLE_EQ(3*0.8,coeffs2.at(0).a);
    ASSERT_DOUBLE_EQ(0,coeffs2.at(0).b);
    ASSERT_DOUBLE_EQ(1./5.,coeffs2.at(0).c);

    ASSERT_DOUBLE_EQ(3*(-2),coeffs2.at(1).a);
    ASSERT_DOUBLE_EQ(2*2.4,coeffs2.at(1).b);
    ASSERT_DOUBLE_EQ(2.6,coeffs2.at(1).c);

    ASSERT_DOUBLE_EQ(3*1.2,coeffs2.at(2).a);
    ASSERT_DOUBLE_EQ(2*(-3.6),coeffs2.at(2).b);
    ASSERT_DOUBLE_EQ(1.4,coeffs2.at(2).c);

}
#include "test_macros.hpp"
TEST_F(SplinesTest, should_be_able_to_compute_position_of_minimum)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const double xmin = a.random<double>();
        const double xmax = a.random<double>().greater_than(xmin);
        const double xmid = (xmin+xmax)/2.;
        const double ymin = a.random<double>().between(-1000,0);
        NaturalSplines s(xmin,xmax,{5,4,3,2,1,ymin,1,2,3,4,5});
        const auto minimum = s.find_position_and_value_of_minimum();
        ASSERT_SMALL_RELATIVE_ERROR(xmid, minimum.first, EPS);
        ASSERT_SMALL_RELATIVE_ERROR(ymin, minimum.second, EPS);
    }
}

TEST_F(SplinesTest, bug_in_min_computation)
{
    const double xmin = -9.101;
    const double xmax = -xmin;
    NaturalSplines s(xmin,xmax,{1481633085564.5,1086836315872.4,786986140477.4,582082559379.5,472125572578.9,457115180075.4,537051381869.0,711934177959.80126953,981763568347.75585938,1346539553032.8674316,1806262132015.1352539});
    ASSERT_SMALL_RELATIVE_ERROR(-0.62150157748417023, s.find_position_and_value_of_minimum().first, EPS);
}

TEST_F(SplinesTest, bug2_in_min_computation)
{
    const std::vector<double> y = {15.11546161820128418, 11.570972870142302246, 9.1584638137532995605, 7.8779344490342663574, 7.7293847759852185059, 8.7128147946061462402, 10.828224504897049561, 14.075613906857929688, 18.45498300048878418, 23.966331785789619141, 30.60966026276043457};
    const double xmin = -9.1099999999999905498;
    const double xmax = -xmin;
    NaturalSplines s(xmin,xmax,y);

    ASSERT_NEAR(-2.49, s.find_position_and_value_of_minimum().first, 0.1);
}
