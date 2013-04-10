/*
 * LongitudeLatitudeTest.cpp
 *
 * \date 28 mars 2013, 11:30:35
 *  \author cec
 */

#include "LongitudeLatitudeTest.hpp"
#include "LongitudeLatitude.hpp"
#include "LongitudeLatitudeGenerators.hpp"

LongitudeLatitudeTest::LongitudeLatitudeTest() : a(DataGenerator(22))
{
}

LongitudeLatitudeTest::~LongitudeLatitudeTest()
{
}

void LongitudeLatitudeTest::SetUp()
{
}

void LongitudeLatitudeTest::TearDown()
{
}

TEST_F(LongitudeLatitudeTest, example)
{
//! [LongitudeLatitudeTest example]
    LongitudeLatitude ll(123,45);
//! [LongitudeLatitudeTest example]
//! [LongitudeLatitudeTest expected output]
    ASSERT_EQ(123, ll.lon);
    ASSERT_EQ(45, ll.lat);
    ASSERT_THROW(LongitudeLatitude(a.random<double>().between(-180,180),a.random<double>().outside(-180,180)),LatitudeLongitudeException);
//! [LongitudeLatitudeTest expected output]
}

TEST_F(LongitudeLatitudeTest, constructor_should_throw_if_input_is_not_bounded)
{
    for (size_t i = 0 ; i < 10000 ; ++i)
    {
        ASSERT_THROW(LongitudeLatitude(a.random<double>().between(-180,180),a.random<double>().between(-180,-90)),LatitudeLongitudeException);
        ASSERT_THROW(LongitudeLatitude(a.random<double>().between(-180,180),a.random<double>().between(90,180)),LatitudeLongitudeException);
        ASSERT_THROW(LongitudeLatitude(a.random<double>().outside(-180,180),a.random<double>().between(-90,90)),LatitudeLongitudeException);
        ASSERT_THROW(LongitudeLatitude(a.random<double>().outside(-180,180),a.random<double>().between(-180,-90)),LatitudeLongitudeException);
        ASSERT_THROW(LongitudeLatitude(a.random<double>().outside(-180,180),a.random<double>().between(90,180)),LatitudeLongitudeException);
    }
}


