/*
 * SplineTest.cpp
 *
 * \date 8 juin 2012, 17:07:12
 *  \author cec
 */

#include "SplinesTest.hpp"
#include "extra_test_assertions.hpp"
#include "NaturalSplines.hpp"
#include <math.h>
#include "VectorOfEquallySpacedNumbers.hpp"
#include "VectorOfEquallySpacedNumbersException.hpp"
#include "InterpolatorException.hpp"
#include "SplinesException.hpp"

#define min(a,b) a<b ? a : b;
#define max(a,b) a>b ? a : b;

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
	ASSERT_DOUBLE_EQ(2.4,spline.d2f(3));
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
		const double lower_bound = min(y.at(i),y.at(i+1));
		const double upper_bound = max(y.at(i),y.at(i+1));
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
	ASSERT_NO_THROW(NaturalSplines(0, 0,a_vector_with_one_element));
}

TEST_F(SplinesTest, should_be_able_to_build_an_empty_spline)
{
	NaturalSplines s;
	ASSERT_EQ(0, s.f(a.random<double>()));
	ASSERT_EQ(0, s.df(a.random<double>()));
	ASSERT_EQ(0, s.d2f(a.random<double>()));
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
    ASSERT_NO_THROW(spline.d2f(x0));
}

TEST_F(SplinesTest, should_be_able_to_retrieve_parabolic_coefficients)
{
    /*const std::vector<double> y = {1.0000,0.9397,0.7660,0.5000,0.1736,-0.1736,-0.5000,-0.7660,-0.9397,-1.0000};
    const NaturalSplines spline1(0, 1,y);
    auto coeffs = spline1.get_parabolic_coefficients();

    ASSERT_EQ(y.size()-1, coeffs.size());*/

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
