/*
 * CubicSplineFunctorTest.cpp
 *
 * \date 19 févr. 2013, 09:38:01
 *  \author cec
 */

#include "SplineFunctorTest.hpp"
#include "SplineFunctor.hpp"

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

    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **x = a.random<double>().between(0,1);
        ASSERT_DOUBLE_EQ(1./5.+(12./5.)*X*X,df_dx());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **x = a.random<double>().between(1,2);
        ASSERT_DOUBLE_EQ(-41./5.+(84./5.)*X-6*X*X,df_dx());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **x = a.random<double>().between(2,3);
        ASSERT_DOUBLE_EQ(151./5.-(108./5.)*X+(18./5.)*X*X,df_dx());
    }

}
/*
TEST_F(CubicSplineFunctorTest, second_derivative_should_be_piecewise_linear)
{
    auto x = generate.state("x");
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const double xmin = a.random<double>();
        const double xmax = a.random<double>().greater_than(xmin);
        const size_t n = a.random<size_t>().greater_than(1).but().no().greater_than(10000);
        const CubicSplineFunctor pc(x, xmin, xmax, a.random_vector_of<double>().of_size(n));
        const auto f = pc.diff(x)->diff(x)->get_lambda();
        **x = a.random<double>();
        ASSERT_EQ(0,f());
    }
}

TEST_F(CubicSplineFunctorTest, third_derivative_should_be_piecewise_constant)
{
}

TEST_F(CubicSplineFunctorTest, fourth_derivative_should_be_zero)
{
}


TEST_F(CubicSplineFunctorTest, should_be_able_to_use_piecewise_as_regular_functor)
{
    auto x = generate.state("x");
    const CubicSplineFunctor pl(x, 0, 10, {3,6,5,8,7,4,5,6,9,72,-56});
    const auto F = 2*x+pl;
    const auto f = F->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **x = a.random<double>().between(0,1);
        ASSERT_DOUBLE_EQ(5*(**x)+3, f());
    }
}
*/
