/*
 * IntegrateOscillatoryTest.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: cady
 */


#include "IntegrateOscillatoryTest.hpp"
#include "ssc/integrate/IntegrateOscillatory.hpp"

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
    ssc::integrate::IntegrateOscillatory I([](const double omega){return log(omega);});
//! [IntegrateOscillatoryTest example]
//! [IntegrateOscillatoryTest expected output]
//! [IntegrateOscillatoryTest expected output]
}



