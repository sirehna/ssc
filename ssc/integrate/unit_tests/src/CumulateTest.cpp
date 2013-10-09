/*
 * CumulateTest.cpp
 *
 * \date 8 oct. 2013, 08:22:10
 *  \author cec
 */

#include "CumulateTest.hpp"
#include "Cumulate.hpp"
#include "CumulateException.hpp"

#include "test_macros.hpp"

CumulateTest::CumulateTest() : a(DataGenerator(22))
{
}

CumulateTest::~CumulateTest()
{
}

void CumulateTest::SetUp()
{
}

void CumulateTest::TearDown()
{
}

TEST_F(CumulateTest, example)
{
//! [CumulateTest example]
    Cumulate c;
    c.add(1,1);
    ASSERT_THROW(c.integrate(a.random<double>(),a.random<double>()),CumulateException);
    c.add(2,2);
    ASSERT_DOUBLE_EQ(1.5, c.integrate(1,2));
    c.add(3,2);
    ASSERT_DOUBLE_EQ(1.5, c.integrate(1,2));
    ASSERT_DOUBLE_EQ(2, c.integrate(2,3));
    ASSERT_DOUBLE_EQ(3.5, c.integrate(1,3));
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        ASSERT_NO_THROW(c.integrate(a.random<double>().between(1,3),a.random<double>().between(1,3)));
        const double x0 =  a.random<double>().between(1,3);
        ASSERT_DOUBLE_EQ(0, c.integrate(x0,x0));
    }
    c.add(2.5,80);
    ASSERT_DOUBLE_EQ(42.5, c.integrate(1,3));
//! [CumulateTest example]
//! [CumulateTest expected output]
//! [CumulateTest expected output]
}



