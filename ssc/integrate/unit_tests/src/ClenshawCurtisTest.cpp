/*
 * IntegrateOscillatoryTest.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: cady
 */


#include "ClenshawCurtisTest.hpp"
#include "ssc/integrate/ClenshawCurtisSine.hpp"

#define _USE_MATH_DEFINE
#include <cmath>
#define PI M_PI

ClenshawCurtisTest::ClenshawCurtisTest() : a(ssc::random_data_generator::DataGenerator(54212))
{
}

ClenshawCurtisTest::~ClenshawCurtisTest()
{
}

void ClenshawCurtisTest::SetUp()
{
}

void ClenshawCurtisTest::TearDown()
{
}

TEST_F(ClenshawCurtisTest, sin)
{
//! [IntegrateOscillatoryTest example]
    ssc::integrate::ClenshawCurtisSine I([](const double omega){return sin(omega);}, 1);
//! [IntegrateOscillatoryTest example]
//! [IntegrateOscillatoryTest expected output]
    const double expected = 0.2726756432935796; // - ( gamma + log(10*PI) - ci(10*pi) ) / (10*pi)

    ASSERT_NEAR(expected, I.integrate_f(0,1,1E-3), 1E-7);
//! [IntegrateOscillatoryTest expected output]
}

