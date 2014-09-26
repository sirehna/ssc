/*
 * LongitudeLatitudeTest.cpp
 *
 * \date 28 mars 2013, 11:30:35
 *  \author cec
 */

#include "LatitudeLongitudeTest.hpp"
#include "LatitudeLongitude.hpp"
#include "LatitudeLongitudeGenerators.hpp"

LatitudeLongitudeTest::LatitudeLongitudeTest() : a(ssc::random_data_generator::DataGenerator(22))
{
}

LatitudeLongitudeTest::~LatitudeLongitudeTest()
{
}

void LatitudeLongitudeTest::SetUp()
{
}

void LatitudeLongitudeTest::TearDown()
{
}

TEST_F(LatitudeLongitudeTest, example)
{
//! [LongitudeLatitudeTest example]
    LatitudeLongitude ll(45,123);
//! [LongitudeLatitudeTest example]
//! [LongitudeLatitudeTest expected output]
    ASSERT_EQ(123, ll.lon);
    ASSERT_EQ(45, ll.lat);
    ASSERT_THROW(LatitudeLongitude(a.random<double>().outside(-180,180),a.random<double>().between(-180,180)),LatitudeLongitudeException);
//! [LongitudeLatitudeTest expected output]
}

TEST_F(LatitudeLongitudeTest, constructor_should_throw_if_input_is_not_bounded)
{
    for (size_t i = 0 ; i < 10000 ; ++i)
    {
        ASSERT_THROW(LatitudeLongitude(a.random<double>().between(-180,-90),a.random<double>().between(-180,180)),LatitudeLongitudeException);
        ASSERT_THROW(LatitudeLongitude(a.random<double>().between(90,180),a.random<double>().between(-180,180)),LatitudeLongitudeException);
        ASSERT_THROW(LatitudeLongitude(a.random<double>().between(-90,90),a.random<double>().outside(-180,180)),LatitudeLongitudeException);
        ASSERT_THROW(LatitudeLongitude(a.random<double>().between(-180,-90),a.random<double>().outside(-180,180)),LatitudeLongitudeException);
        ASSERT_THROW(LatitudeLongitude(a.random<double>().between(90,180),a.random<double>().outside(-180,180)),LatitudeLongitudeException);
    }
}


