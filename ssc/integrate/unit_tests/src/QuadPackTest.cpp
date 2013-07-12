/*
 * QuadPackTest.cpp
 *
 * \date 5 juil. 2013, 13:32:10
 *  \author cec
 */

#include "QuadPackTest.hpp"
#include "QuadPack.hpp"

QuadPackTest::QuadPackTest() : a(DataGenerator(2))
{
}

QuadPackTest::~QuadPackTest()
{
}

void QuadPackTest::SetUp()
{
}

void QuadPackTest::TearDown()
{
}



TEST_F(QuadPackTest, example)
{
    //! [QuadPackTest example]
    QuadPack integrator([](double x){return x*x;});
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double a_ = a.random<double>().between(-10,0);
        const double b_ = a.random<double>().between(0,10);
        ASSERT_DOUBLE_EQ((b_*b_*b_-a_*a_*a_)/3.,integrator.integrate(a_,b_));
    }
    //! [QuadPackTest example]
}

TEST_F(QuadPackTest, sinc)
{
    QuadPack integrator([](double x){return sin(x)*sin(x)+cos(x)*cos(x);});
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double a_ = a.random<double>().between(-10,0);
        const double b_ = a.random<double>().between(0,10);
        ASSERT_DOUBLE_EQ(b_-a_,integrator.integrate(a_,b_));
    }
}

