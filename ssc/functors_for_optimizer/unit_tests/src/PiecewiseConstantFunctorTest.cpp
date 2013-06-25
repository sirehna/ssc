/*
 * PiecewiseConstantFunctor.cpp
 *
 * \date 18 févr. 2013, 17:19:21
 *  \author cec
 */

#include "PiecewiseConstantFunctorTest.hpp"
#include "PiecewiseConstantFunctor.hpp"
#include "FunctorAlgebra.hpp"
#include "Sum.hpp"
#include "extra_test_assertions.hpp"

PiecewiseConstantFunctorTest::PiecewiseConstantFunctorTest() : a(DataGenerator(669)),
generate(StateGenerator())
{
}

PiecewiseConstantFunctorTest::~PiecewiseConstantFunctorTest()
{
}

void PiecewiseConstantFunctorTest::SetUp()
{
}

void PiecewiseConstantFunctorTest::TearDown()
{
}

TEST_F(PiecewiseConstantFunctorTest, example)
{
//! [PiecewiseConstantFunctor example]
    auto x = generate.state("x");
    PiecewiseConstantFunctor pc(x, 0, 10, {3,6,5,8,7,4,5,6,9,72});
    const auto f = pc.get_lambda();
//! [PiecewiseConstantFunctor example]
//! [PiecewiseConstantFunctor expected output]
    *x = a.random<double>().between(0,1);
    ASSERT_DOUBLE_EQ(3, f());
    *x = a.random<double>().between(1,2);
    ASSERT_DOUBLE_EQ(6, f());
    *x = a.random<double>().between(2,3);
    ASSERT_DOUBLE_EQ(5, f());
    *x = a.random<double>().between(3,4);
    ASSERT_DOUBLE_EQ(8, f());
    *x = a.random<double>().greater_than(10);
    ASSERT_DOUBLE_EQ(72, f());
//! [PiecewiseConstantFunctor expected output]
}

TEST_F(PiecewiseConstantFunctorTest, first_derivative_should_be_zero)
{
    auto x = generate.state("x");
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const double xmin = a.random<double>();
        const double xmax = a.random<double>().greater_than(xmin);
        size_t n = a.random<size_t>().greater_than(1).but().no().greater_than(1000);
        n = n<=1 ? 2 : n;
        const PiecewiseConstantFunctor pc(x, xmin, xmax, a.random_vector_of<double>().of_size(n));
        const auto f = pc.diff(x)->get_lambda();
        *x = a.random<double>();
        ASSERT_EQ(0,f());
    }
}

TEST_F(PiecewiseConstantFunctorTest, should_be_able_to_use_piecewise_as_regular_functor)
{
    auto x = generate.state("x");
    #define X (x->get_lambda()())

    PiecewiseConstantFunctor pc(x, 0, 10, {3,6,5,8,7,4,5,6,9,72});
    const auto F = 2*x+pc;
    const auto f = F->get_lambda();
    *x = a.random<double>().between(0,1);
    ASSERT_DOUBLE_EQ(2*X+3, f());
    *x = a.random<double>().between(1,2);
    ASSERT_DOUBLE_EQ(2*X+6, f());
    *x = a.random<double>().between(2,3);
    ASSERT_DOUBLE_EQ(2*X+5, f());
    *x = a.random<double>().between(3,4);
    ASSERT_DOUBLE_EQ(2*X+8, f());
    *x = a.random<double>().greater_than(10);
    ASSERT_SMALL_RELATIVE_ERROR(2*X+72, f(), 1E-7);
}
