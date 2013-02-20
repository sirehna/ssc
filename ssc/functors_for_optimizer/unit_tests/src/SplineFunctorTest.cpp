/*
 * CubicSplineFunctorTest.cpp
 *
 * \date 19 févr. 2013, 09:38:01
 *  \author cec
 */

#include "SplineFunctorTest.hpp"
#include "SplineFunctor.hpp"
#include "extra_test_assertions.hpp"
#include "FunctorAlgebra.hpp"
#include "Sum.hpp"

SplineFunctorTest::SplineFunctorTest() : a(DataGenerator(7779988)),
                                                   generate(StateGenerator())
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
    auto x = generate.state("x");
    SplineFunctor functor(x, 0, 10, {3,6,5,8,7,4,5,6,9,72,-56});
    const auto f = functor.get_lambda();
//! [SplineFunctorTest example]
//! [SplineFunctorTest expected output]
    **x = 0;
    ASSERT_DOUBLE_EQ(3, f());
    **x = 1;
    ASSERT_DOUBLE_EQ(6, f());
//! [SplineFunctorTest expected output]
}

TEST_F(SplineFunctorTest, value_should_be_computed_properly)
{
    auto x = generate.state("x");
    SplineFunctor pl(x, 0, 10, {2,4,6,1,8,7,9,10,1,4,6});
    const auto f = pl.get_lambda();
    **x = 0.3;
    ASSERT_DOUBLE_EQ(2.3876418091940046, f());
    **x = 1.7;
    ASSERT_DOUBLE_EQ(6.2984384995638267, f());
    **x = 2.25;
    ASSERT_DOUBLE_EQ(4.676882732163155, f());
    **x = 3.697;
    ASSERT_DOUBLE_EQ(5.8705490717423414, f());
}

TEST_F(SplineFunctorTest, first_derivative_should_be_piecewise_parabolic)
{
    auto x = generate.state("x");
    #define X (**x)

    SplineFunctor pl(x, 0, 3, {0,1,4,3});
    const auto df_dx = pl.diff(x)->get_lambda();
    const double eps = 1e-10;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(0,1);
        ASSERT_SMALL_RELATIVE_ERROR(0.2+(3*0.8)*X*X,df_dx(),eps);
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(1,2);
        ASSERT_SMALL_RELATIVE_ERROR(2.6+(2*2.4)*(X-1)-3*2*(X-1)*(X-1),df_dx(),eps);
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(2,3);
        ASSERT_SMALL_RELATIVE_ERROR(1.4-(2*3.6)*(X-2)+(3*1.2)*(X-2)*(X-2),df_dx(),eps);
    }

}

TEST_F(SplineFunctorTest, second_derivative_should_be_piecewise_linear)
{
    auto x = generate.state("x");
    #define X (**x)
    SplineFunctor pl(x, 0, 3, {0,1,4,3});
    const auto d2f_dx2 = pl.diff(x)->diff(x)->get_lambda();
    const double eps = 1e-10;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(0,1);
        ASSERT_SMALL_RELATIVE_ERROR(2*(3*0.8)*X,d2f_dx2(),eps);
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(1,2);
        ASSERT_SMALL_RELATIVE_ERROR((2*2.4)-2*3*2*(X-1),d2f_dx2(),eps);
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(2,3);
        ASSERT_SMALL_RELATIVE_ERROR(-(2*3.6)+2*(3*1.2)*(X-2),d2f_dx2(),eps);
    }
}

TEST_F(SplineFunctorTest, third_derivative_should_be_piecewise_constant)
{
    auto x = generate.state("x");
    #define X (**x)
    SplineFunctor pl(x, 0, 3, {0,1,4,3});
    const auto d3f_dx3 = pl.diff(x)->diff(x)->diff(x)->get_lambda();
    const double eps = 1e-10;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(0,1);
        ASSERT_SMALL_RELATIVE_ERROR(2*3*0.8,d3f_dx3(),eps);
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(1,2);
        ASSERT_SMALL_RELATIVE_ERROR(-2*3*2,d3f_dx3(),eps);
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(2,3);
        ASSERT_SMALL_RELATIVE_ERROR(2*(3*1.2),d3f_dx3(),eps);
    }
}

TEST_F(SplineFunctorTest, fourth_derivative_should_be_zero)
{
    auto x = generate.state("x");
    #define X (**x)
    SplineFunctor pl(x, 0, 3, {0,1,4,3});
    const auto d4f_dx4 = pl.diff(x)->diff(x)->diff(x)->diff(x)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>();
        ASSERT_EQ(0,d4f_dx4());
    }
}


TEST_F(SplineFunctorTest, should_be_able_to_use_spline_as_regular_functor)
{
    auto x = generate.state("x");
    const SplineFunctor pl(x, 0, 10, {3,6,5,8,7,4,5,6,9,72,-56});
    const auto F = 2*x+pl;
    const auto f = F->get_lambda();
    **x = 0;
    ASSERT_DOUBLE_EQ(2*(**x)+3, f());
    **x = 1;
    ASSERT_DOUBLE_EQ(2*(**x)+6, f());
    **x = 2;
    ASSERT_DOUBLE_EQ(2*(**x)+5, f());
    **x = 3;
    ASSERT_DOUBLE_EQ(2*(**x)+8, f());
    **x = 4;
    ASSERT_DOUBLE_EQ(2*(**x)+7, f());
    **x = 5;
    ASSERT_DOUBLE_EQ(2*(**x)+4, f());
    **x = 6;
    ASSERT_DOUBLE_EQ(2*(**x)+5, f());
    **x = 7;
    ASSERT_DOUBLE_EQ(2*(**x)+6, f());
    **x = 8;
    ASSERT_DOUBLE_EQ(2*(**x)+9, f());
    **x = 9;
    ASSERT_DOUBLE_EQ(2*(**x)+72, f());
    **x = 10;
    ASSERT_DOUBLE_EQ(2*(**x)-56, f());
}

