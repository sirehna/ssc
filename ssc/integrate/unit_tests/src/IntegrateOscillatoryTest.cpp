/*
 * IntegrateOscillatoryTest.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: cady
 */


#include "IntegrateOscillatoryTest.hpp"
#include "ssc/integrate/IntegrateOscillatory.hpp"

#define _USE_MATH_DEFINE
#include <cmath>
#define PI M_PI

IntegrateOscillatoryTest::IntegrateOscillatoryTest() : a(ssc::random_data_generator::DataGenerator(54212))
{
}

IntegrateOscillatoryTest::~IntegrateOscillatoryTest()
{
}

void IntegrateOscillatoryTest::SetUp()
{
}

void IntegrateOscillatoryTest::TearDown()
{
}

TEST_F(IntegrateOscillatoryTest, example)
{
//! [IntegrateOscillatoryTest example]
    ssc::integrate::ClenshawCurtis I([](const double omega){return log(omega);}, 10*PI);
//! [IntegrateOscillatoryTest example]
//! [IntegrateOscillatoryTest expected output]
    const double expected = -0.1281316; // - ( gamma + log(10*PI) - ci(10*pi) ) / (10*pi)

    ASSERT_NEAR(expected, I.integrate_f(0,1,1E-3), 1E-7);
//! [IntegrateOscillatoryTest expected output]
}



