/*
 * AddPointToIntegralTest.cpp
 *
 * \date 10 juin 2013, 10:04:01
 *  \author cec
 */

#include "AddPointToIntegralTest.hpp"


#include "AddPointToIntegral.hpp"

AddPointToIntegralTest::AddPointToIntegralTest() : a(DataGenerator(1))
{
}

AddPointToIntegralTest::~AddPointToIntegralTest()
{
}

void AddPointToIntegralTest::SetUp()
{
}

void AddPointToIntegralTest::TearDown()
{
}

TEST_F(AddPointToIntegralTest, example)
{
//! [AddPointToIntegralTest example]
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double lambda = 1;//a.random<double>();
        const double mu = 2;//a.random<double>();
        const double x1 = 3;//a.random<double>();
        const double x2 = 4;//a.random<double>();
        const double x3 = 5;//a.random<double>();
        const double y1 = lambda*x1+mu;
        const double y2 = lambda*x2+mu;
        const double y3 = lambda*x3+mu;
        const double I1 = integrate(0, y1, y2, x2-x1);
        const double I2 = integrate(I1, y2, y3, x3-x2);
//! [AddPointToIntegralTest example]
//! [AddPointToIntegralTest expected output]
        ASSERT_DOUBLE_EQ((x2-x1)*(lambda/2*(x1+x2)+mu), I1);
        ASSERT_DOUBLE_EQ(I1+(x3-x2)*(lambda/2*(x3+x2)+mu), I2);
//! [AddPointToIntegralTest expected output]
    }
}



