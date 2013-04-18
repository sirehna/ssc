/*
 * PointInCartesianPolygonTest.cpp
 *
 * \date 27 mars 2013, 16:10:07
 *  \author cec
 */

#include "PointInCartesianPolygonTest.hpp"
#include "PointInCartesianPolygon.hpp"
#include "LongitudeLatitudeGenerators.hpp"

PointInCartesianPolygonTest::PointInCartesianPolygonTest() : a(DataGenerator(997788))
{
}

PointInCartesianPolygonTest::~PointInCartesianPolygonTest()
{
}

void PointInCartesianPolygonTest::SetUp()
{
}

void PointInCartesianPolygonTest::TearDown()
{
}

TEST_F(PointInCartesianPolygonTest, example)
{
//! [PointInCartesianPolygonTest example]
    // Start by declaring a zone
    std::vector<LongitudeLatitude> zone;
    zone.push_back(LongitudeLatitude(-117.101833, 32.535000));
    zone.push_back(LongitudeLatitude(-117.121500, 32.534000));
    zone.push_back(LongitudeLatitude(-117.236667, 32.523167));
    zone.push_back(LongitudeLatitude(-117.258333, 32.552167));
    zone.push_back(LongitudeLatitude(-117.366833, 32.570167));
    zone.push_back(LongitudeLatitude(-117.458833, 32.587167));
    zone.push_back(LongitudeLatitude(-117.822333, 32.623000));
    zone.push_back(LongitudeLatitude(-118.603500, 31.126500));
    zone.push_back(LongitudeLatitude(-121.788167, 30.554167));
    zone.push_back(LongitudeLatitude(-123.287000, 31.768500));
    zone.push_back(LongitudeLatitude(-123.840667, 32.359667));
    zone.push_back(LongitudeLatitude(-124.191167, 32.939833));
    zone.push_back(LongitudeLatitude(-124.452500, 33.668667));
    zone.push_back(LongitudeLatitude(-125.275333, 34.521333));
    zone.push_back(LongitudeLatitude(-125.720500, 35.239667));
    zone.push_back(LongitudeLatitude(-126.308833, 35.726667));
    zone.push_back(LongitudeLatitude(-126.755000, 36.270833));
    zone.push_back(LongitudeLatitude(-127.119667, 37.022500));
    zone.push_back(LongitudeLatitude(-127.633667, 37.756500));
    zone.push_back(LongitudeLatitude(-127.876667, 38.418000));
    zone.push_back(LongitudeLatitude(-128.520500, 39.417500));
    zone.push_back(LongitudeLatitude(-128.757667, 40.307833));
    zone.push_back(LongitudeLatitude(-128.670333, 41.223167));
    zone.push_back(LongitudeLatitude(-129.006333, 42.208167));
    zone.push_back(LongitudeLatitude(-129.090333, 42.789000));
    zone.push_back(LongitudeLatitude(-129.021000, 43.437000));
    zone.push_back(LongitudeLatitude(-128.687167, 44.407167));
    zone.push_back(LongitudeLatitude(-128.667000, 45.507167));
    zone.push_back(LongitudeLatitude(-128.816833, 46.183500));
    zone.push_back(LongitudeLatitude(-129.071500, 46.559167));
    zone.push_back(LongitudeLatitude(-131.256833, 47.659167));
    zone.push_back(LongitudeLatitude(-132.683333, 48.538667));
    zone.push_back(LongitudeLatitude(-133.241167, 48.957833));
    zone.push_back(LongitudeLatitude(-134.258500, 49.373167));
    zone.push_back(LongitudeLatitude(-135.316833, 50.025333));
    zone.push_back(LongitudeLatitude(-136.757500, 51.053000));
    zone.push_back(LongitudeLatitude(-137.692333, 51.900667));
    zone.push_back(LongitudeLatitude(-138.335667, 52.752000));
    zone.push_back(LongitudeLatitude(-138.672667, 53.486667));
    zone.push_back(LongitudeLatitude(-138.808833, 53.673167));
    zone.push_back(LongitudeLatitude(-139.539667, 54.224167));
    zone.push_back(LongitudeLatitude(-139.936500, 54.654167));
    zone.push_back(LongitudeLatitude(-140.924167, 55.336333));
    zone.push_back(LongitudeLatitude(-141.603000, 56.118667));
    zone.push_back(LongitudeLatitude(-142.286500, 56.472000));
    zone.push_back(LongitudeLatitude(-142.809500, 56.619833));
    zone.push_back(LongitudeLatitude(-153.250500, 58.850667));
    zone.push_back(LongitudeLatitude(-140.657281, 61.141487));
    zone.push_back(LongitudeLatitude(-119.457813, 47.718672));
    zone.push_back(LongitudeLatitude(-123.824749, 40.227427));
    zone.push_back(LongitudeLatitude(-116.627637, 32.974717));
    zone.push_back(LongitudeLatitude(-117.101833, 32.535000)); // Polygon needs to be closed
    // Then build a PointInCartesianPolygon object
    const PointInCartesianPolygon eca(zone);
//! [PointInCartesianPolygonTest example]
//! [PointInCartesianPolygonTest expected output]
    // This object can then be asked if a point is in the zone or not
    ASSERT_FALSE(eca.is_in_polygon(LongitudeLatitude(0,0)));
    //ASSERT_TRUE(eca.is_in_zone(LatitudeLongitude(-120,35)));
    ASSERT_TRUE(eca.is_in_polygon(LongitudeLatitude(-126,40)));
//! [PointInCartesianPolygonTest expected output]
}

TEST_F(PointInCartesianPolygonTest, simple_triangle_example)
{
    std::vector<LongitudeLatitude> zone;
    zone.push_back(LongitudeLatitude(0,0));
    zone.push_back(LongitudeLatitude(80,0));
    zone.push_back(LongitudeLatitude(40,40));
    zone.push_back(LongitudeLatitude(0,0));

    const PointInCartesianPolygon eca(zone);

    ASSERT_TRUE(eca.is_in_polygon(LongitudeLatitude(40,20)));
    ASSERT_TRUE(eca.is_in_polygon(LongitudeLatitude(15,10)));
    ASSERT_FALSE(eca.is_in_polygon(LongitudeLatitude(16.1,20)));
    ASSERT_TRUE(eca.is_in_polygon(LongitudeLatitude(23,18.98)));
    ASSERT_TRUE(eca.is_in_polygon(LongitudeLatitude(23,18.975)));
    ASSERT_TRUE(eca.is_in_polygon(LongitudeLatitude(23,18.97)));
    ASSERT_TRUE(eca.is_in_polygon(LongitudeLatitude(20,16.2)));
    ASSERT_TRUE(eca.is_in_polygon(LongitudeLatitude(20,16.19)));
    ASSERT_TRUE(eca.is_in_polygon(LongitudeLatitude(20,16.185)));
}

TEST_F(PointInCartesianPolygonTest, constructor_should_throw_if_received_less_than_three_points)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        std::vector<LongitudeLatitude> zone;
        ASSERT_THROW(PointInCartesianPolygon p1(zone), PointInPolygonException);
        zone.push_back(a.random<LongitudeLatitude>());
        ASSERT_THROW(PointInCartesianPolygon p2(zone), PointInPolygonException);
        zone.push_back(a.random<LongitudeLatitude>());
        ASSERT_THROW(PointInCartesianPolygon p3(zone), PointInPolygonException);
        zone.push_back(zone.front());
        ASSERT_NO_THROW(PointInCartesianPolygon p4(zone));
    }
}

TEST_F(PointInCartesianPolygonTest, constructor_should_throw_if_polygon_is_not_closed)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(3,200);
        std::vector<LongitudeLatitude> zone = a.random_vector_of<LongitudeLatitude>().of_size(n);
        ASSERT_THROW(PointInCartesianPolygon p1(zone), PointInPolygonException);
        zone.push_back(zone.front());
        ASSERT_NO_THROW(PointInCartesianPolygon p2(zone));
    }
}
