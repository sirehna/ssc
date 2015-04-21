/*
 * PiecewiseLinearFunctorTest.cpp
 *
 * \date 19 f�vr. 2013, 08:34:47
 *  \author cec
 */

#include "PiecewiseLinearFunctorTest.hpp"
#include "ssc/functors_for_optimizer/PiecewiseLinearFunctor.hpp"
#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"
#include "ssc/functors_for_optimizer/Sum.hpp"

using namespace ssc::functors_for_optimizer;

PiecewiseLinearFunctorTest::PiecewiseLinearFunctorTest() : a(ssc::random_data_generator::DataGenerator(11)),
generate(StateGenerator())
{
}

PiecewiseLinearFunctorTest::~PiecewiseLinearFunctorTest()
{
}

void PiecewiseLinearFunctorTest::SetUp()
{
}

void PiecewiseLinearFunctorTest::TearDown()
{
}

TEST_F(PiecewiseLinearFunctorTest, example)
{
//! [PiecewiseLinearFunctorTest example]
    auto x = generate.state("x");
    std::vector<double> v;
    v.push_back(3);v.push_back(6);v.push_back(5);v.push_back(8);v.push_back(7);v.push_back(4);v.push_back(5);v.push_back(6);v.push_back(9);v.push_back(72);v.push_back(-56);
    PiecewiseLinearFunctor pl(x, 0, 10, v);
    const auto f = pl.get_lambda();
//! [PiecewiseLinearFunctorTest example]
//! [PiecewiseLinearFunctorTest expected output]
    *x = 0;
    ASSERT_DOUBLE_EQ(3, f());
    *x = 0.5;
    ASSERT_DOUBLE_EQ(4.5, f());
//! [PiecewiseLinearFunctorTest expected output]
}

TEST_F(PiecewiseLinearFunctorTest, value_should_be_computed_properly)
{
    auto x = generate.state("x");
    std::vector<double> v;
    v.push_back(3);v.push_back(6);v.push_back(5);v.push_back(8);v.push_back(7);v.push_back(4);v.push_back(5);v.push_back(6);v.push_back(9);v.push_back(72);v.push_back(-56);
    PiecewiseLinearFunctor pl(x, 0, 10, v);
    const auto f = pl.get_lambda();
    *x = 1.5;
    ASSERT_DOUBLE_EQ(5.5, f());
    *x = 2.7;
    ASSERT_DOUBLE_EQ(5+0.7*3, f());
}
TEST_F(PiecewiseLinearFunctorTest, first_derivative_should_be_piecewise_constant)
{
    auto x = generate.state("x");
    std::vector<double> v;
    v.push_back(3);v.push_back(6);v.push_back(5);v.push_back(8);v.push_back(7);v.push_back(4);v.push_back(5);v.push_back(6);v.push_back(9);v.push_back(72);v.push_back(-56);
    PiecewiseLinearFunctor pl(x, 0, 10, v);
    const auto df_dx = pl.diff(x)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *x = a.random<double>().between(0,1);
        ASSERT_DOUBLE_EQ(3,df_dx());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *x = a.random<double>().between(1,2);
        ASSERT_DOUBLE_EQ(-1,df_dx());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *x = a.random<double>().between(2,3);
        ASSERT_DOUBLE_EQ(3,df_dx());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *x = a.random<double>().between(3,4);
        ASSERT_DOUBLE_EQ(-1,df_dx());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *x = a.random<double>().between(4,5);
        ASSERT_DOUBLE_EQ(-3,df_dx());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *x = a.random<double>().between(5,6);
        ASSERT_DOUBLE_EQ(1,df_dx());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *x = a.random<double>().between(6,7);
        ASSERT_DOUBLE_EQ(1,df_dx());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *x = a.random<double>().between(7,8);
        ASSERT_DOUBLE_EQ(3,df_dx());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *x = a.random<double>().between(8,9);
        ASSERT_DOUBLE_EQ(63,df_dx());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *x = a.random<double>().between(9,10);
        ASSERT_DOUBLE_EQ(-128,df_dx());
    }
}

TEST_F(PiecewiseLinearFunctorTest, second_derivative_should_be_zero)
{
    auto x = generate.state("x");
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const double xmin = a.random<double>();
        const double xmax = a.random<double>().greater_than(xmin);
        const size_t n = a.random<size_t>().greater_than(1).but().no().greater_than(10000);
        const PiecewiseLinearFunctor pc(x, xmin, xmax, a.random_vector_of<double>().of_size(n));
        const auto f = pc.diff(x)->diff(x)->get_lambda();
        *x = a.random<double>();
        ASSERT_EQ(0,f());
    }
}

TEST_F(PiecewiseLinearFunctorTest, should_be_second_derivative_even_if_there_are_only_two_y_values)
{
    auto x = generate.state("x");
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const double xmin = a.random<double>();
        const double xmax = a.random<double>().greater_than(xmin);
        const size_t n = 2;
        const PiecewiseLinearFunctor pc(x, xmin, xmax, a.random_vector_of<double>().of_size(n));
        const auto f = pc.diff(x)->diff(x)->get_lambda();
        *x = a.random<double>();
        ASSERT_EQ(0,f());
    }
}

TEST_F(PiecewiseLinearFunctorTest, should_be_able_to_use_piecewise_as_regular_functor)
{
    auto x = generate.state("x");
    std::vector<double> v;
    v.push_back(3);v.push_back(6);v.push_back(5);v.push_back(8);v.push_back(7);v.push_back(4);v.push_back(5);v.push_back(6);v.push_back(9);v.push_back(72);v.push_back(-56);
    const PiecewiseLinearFunctor pl(x, 0, 10, v);
    const auto F = 2*x+pl;
    const auto f = F->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *x = a.random<double>().between(0,1);
        ASSERT_DOUBLE_EQ(5*(x->get_lambda()())+3, f());
    }
}
