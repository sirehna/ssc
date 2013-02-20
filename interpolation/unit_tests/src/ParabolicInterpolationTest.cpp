/*
 * ParabolicInterpolationTest.cpp
 *
 * \date 19 févr. 2013, 09:56:08
 *  \author cec
 */

#include "ParabolicInterpolationTest.hpp"
#include "ParabolicInterpolation.hpp"

ParabolicInterpolationTest::ParabolicInterpolationTest() : a(DataGenerator(77))
{
}

ParabolicInterpolationTest::~ParabolicInterpolationTest()
{
}

void ParabolicInterpolationTest::SetUp()
{
}

void ParabolicInterpolationTest::TearDown()
{
}

TEST_F(ParabolicInterpolationTest, example)
{
//! [ParabolicInterpolationTest example]
    std::vector<ParabolicCoefficients> v;
    v.push_back(ParabolicCoefficients(1,2,3));
    v.push_back(ParabolicCoefficients(4,5,6));
    v.push_back(ParabolicCoefficients(7,8,9));
    v.push_back(ParabolicCoefficients(10,11,12));
    ParabolicInterpolation pi(0,5,v);
//! [ParabolicInterpolationTest example]
//! [ParabolicInterpolationTest expected output]
    double x = 0.5;
    pi.set_computed_value(x);
    ASSERT_DOUBLE_EQ(1*x*x+2*x+3, pi.f());
    x = 1.7;
    pi.set_computed_value(x);
    ASSERT_DOUBLE_EQ(4*x*x+5*x+6, pi.f());
    x = 2.8;
    pi.set_computed_value(x);
    ASSERT_DOUBLE_EQ(7*x*x+8*x+9, pi.f());
//! [ParabolicInterpolationTest expected output]
}



