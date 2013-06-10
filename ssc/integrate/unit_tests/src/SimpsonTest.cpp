/*
 * SimpsonTest.cpp
 *
 * \date 23 avr. 2013, 15:38:05
 *  \author cec
 */

#include "SimpsonTest.hpp"
#include "Simpson.hpp"
#include "extra_test_assertions.hpp"

SimpsonTest::SimpsonTest() : a(DataGenerator(1))
{
}

SimpsonTest::~SimpsonTest()
{
}

void SimpsonTest::SetUp()
{
}

void SimpsonTest::TearDown()
{
}

#define EPS 1E-6

TEST_F(SimpsonTest, should_be_able_to_integrate_x)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
//! [SimpsonTest example]
    Simpson integrator([](const double& x){return x;});
    const double xa = a.random<double>().between(-100,100);
    const double xb = a.random<double>().between(xa,100);
//! [SimpsonTest example]
//! [SimpsonTest expected output]
    ASSERT_SMALL_RELATIVE_ERROR(integrator.integrate(xa,xb), (xb*xb-xa*xa)/2., EPS);
//! [SimpsonTest expected output]
    }
}

TEST_F(SimpsonTest, should_be_able_to_integrate_a_constant)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const double c = a.random<double>();
        Simpson integrator([c](const double& x)->double{(void)x;return c;});
        const double xa = a.random<double>().between(-100,100);
        const double xb = a.random<double>().between(xa,100);
        ASSERT_SMALL_RELATIVE_ERROR(integrator.integrate(xa,xb), (xb-xa)*c, EPS);
    }
}

TEST_F(SimpsonTest, should_be_able_to_integrate_a_parabola)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const double lambda = a.random<double>();
        const double mu = a.random<double>();
        Simpson integrator([&lambda,&mu](const double& x)->double{return lambda*x*x+mu;});
        const double xa = a.random<double>().between(-100,100);
        const double xb = a.random<double>().between(xa,100);
        ASSERT_SMALL_RELATIVE_ERROR(integrator.integrate(xa,xb), lambda*(pow(xb,3)-pow(xa,3))/3.+mu*(xb-xa), EPS);
    }
}









