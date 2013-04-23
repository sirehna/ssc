/*
 * IntegrateTest.cpp
 *
 * \date 23 avr. 2013, 09:46:55
 *  \author cec
 */

#include "IntegrateTest.hpp"
#include "Integrate.hpp"
#include "extra_test_assertions.hpp"

#define EPS 1E-10


IntegrateTest::IntegrateTest() : a(DataGenerator(7))
{
}

IntegrateTest::~IntegrateTest()
{
}

void IntegrateTest::SetUp()
{
}

void IntegrateTest::TearDown()
{
}

TEST_F(IntegrateTest, should_be_able_to_integrate_x)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
//! [IntegrateTest example]
    Integrate integrator([](const double& x){return x;});
    const double xa = a.random<double>().between(-100,100);
    const double xb = a.random<double>().between(xa,100);
//! [IntegrateTest example]
//! [IntegrateTest expected output]
    ASSERT_SMALL_RELATIVE_ERROR(integrator.integrate(xa,xb), (xb*xb-xa*xa)/2., EPS);
//! [IntegrateTest expected output]
    }
}

TEST_F(IntegrateTest, should_be_able_to_integrate_a_constant)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        COUT("");
        const double c = a.random<double>();
        COUT(c);
        Integrate integrator([c](const double& x)->double{(void)x;return c;});
        COUT("");
        const double xa = a.random<double>().between(-100,100);
        COUT(xa);
        const double xb = a.random<double>().between(xa,100);
        COUT(xb);
        ASSERT_SMALL_RELATIVE_ERROR(integrator.integrate(xa,xb), (xb-xa)*c, EPS);
        COUT("");
    }
}

TEST_F(IntegrateTest, should_be_able_to_integrate_a_parabola)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const double lambda = a.random<double>();
        const double mu = a.random<double>();
        Integrate integrator([&lambda,&mu](const double& x)->double{return lambda*x*x+mu;});
        const double xa = a.random<double>().between(-100,100);
        const double xb = a.random<double>().between(xa,100);
        ASSERT_SMALL_RELATIVE_ERROR(integrator.integrate(xa,xb), lambda*pow(xb-xa,3)/3.+mu*(xb-xa), EPS);
    }
}





