/*
 * IntegrateOscillatoryTest.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: cady
 */


#include "ClenshawCurtisTest.hpp"
#include "ssc/integrate/ClenshawCurtis.hpp"

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

TEST_F(ClenshawCurtisTest, example)
{
//! [IntegrateOscillatoryTest example]
    ssc::integrate::ClenshawCurtis I([](const double omega){return log(omega);}, 10*PI);
//! [IntegrateOscillatoryTest example]
//! [IntegrateOscillatoryTest expected output]
    const double expected = -0.1281316; // - ( gamma + log(10*PI) - ci(10*pi) ) / (10*pi)

    ASSERT_NEAR(expected, I.integrate_f(0,1,1E-3), 1E-7);
//! [IntegrateOscillatoryTest expected output]
}



