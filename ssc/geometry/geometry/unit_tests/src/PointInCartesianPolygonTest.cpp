/*
 * PointInCartesianPolygonTest.cpp
 *
 * \date 27 mars 2013, 16:10:07
 *  \author cec
 */

#include "PointInCartesianPolygonTest.hpp"
#include "PointInCartesianPolygon.hpp"
#include "LatitudeLongitudeGenerators.hpp"

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
    std::vector<LatitudeLongitude> zone;
    zone.push_back(LatitudeLongitude( 32.535000,-117.101833));
    zone.push_back(LatitudeLongitude( 32.534000,-117.121500));
    zone.push_back(LatitudeLongitude( 32.523167,-117.236667));
    zone.push_back(LatitudeLongitude( 32.552167,-117.258333));
    zone.push_back(LatitudeLongitude( 32.570167,-117.366833));
    zone.push_back(LatitudeLongitude( 32.587167,-117.458833));
    zone.push_back(LatitudeLongitude( 32.623000,-117.822333));
    zone.push_back(LatitudeLongitude( 31.126500,-118.603500));
    zone.push_back(LatitudeLongitude( 30.554167,-121.788167));
    zone.push_back(LatitudeLongitude( 31.768500,-123.287000));
    zone.push_back(LatitudeLongitude( 32.359667,-123.840667));
    zone.push_back(LatitudeLongitude( 32.939833,-124.191167));
    zone.push_back(LatitudeLongitude( 33.668667,-124.452500));
    zone.push_back(LatitudeLongitude( 34.521333,-125.275333));
    zone.push_back(LatitudeLongitude( 35.239667,-125.720500));
    zone.push_back(LatitudeLongitude( 35.726667,-126.308833));
    zone.push_back(LatitudeLongitude( 36.270833,-126.755000));
    zone.push_back(LatitudeLongitude( 37.022500,-127.119667));
    zone.push_back(LatitudeLongitude( 37.756500,-127.633667));
    zone.push_back(LatitudeLongitude( 38.418000,-127.876667));
    zone.push_back(LatitudeLongitude( 39.417500,-128.520500));
    zone.push_back(LatitudeLongitude( 40.307833,-128.757667));
    zone.push_back(LatitudeLongitude( 41.223167,-128.670333));
    zone.push_back(LatitudeLongitude( 42.208167,-129.006333));
    zone.push_back(LatitudeLongitude( 42.789000,-129.090333));
    zone.push_back(LatitudeLongitude( 43.437000,-129.021000));
    zone.push_back(LatitudeLongitude( 44.407167,-128.687167));
    zone.push_back(LatitudeLongitude( 45.507167,-128.667000));
    zone.push_back(LatitudeLongitude( 46.183500,-128.816833));
    zone.push_back(LatitudeLongitude( 46.559167,-129.071500));
    zone.push_back(LatitudeLongitude( 47.659167,-131.256833));
    zone.push_back(LatitudeLongitude( 48.538667,-132.683333));
    zone.push_back(LatitudeLongitude( 48.957833,-133.241167));
    zone.push_back(LatitudeLongitude( 49.373167,-134.258500));
    zone.push_back(LatitudeLongitude( 50.025333,-135.316833));
    zone.push_back(LatitudeLongitude( 51.053000,-136.757500));
    zone.push_back(LatitudeLongitude( 51.900667,-137.692333));
    zone.push_back(LatitudeLongitude( 52.752000,-138.335667));
    zone.push_back(LatitudeLongitude( 53.486667,-138.672667));
    zone.push_back(LatitudeLongitude( 53.673167,-138.808833));
    zone.push_back(LatitudeLongitude( 54.224167,-139.539667));
    zone.push_back(LatitudeLongitude( 54.654167,-139.936500));
    zone.push_back(LatitudeLongitude( 55.336333,-140.924167));
    zone.push_back(LatitudeLongitude( 56.118667,-141.603000));
    zone.push_back(LatitudeLongitude( 56.472000,-142.286500));
    zone.push_back(LatitudeLongitude( 56.619833,-142.809500));
    zone.push_back(LatitudeLongitude( 58.850667,-153.250500));
    zone.push_back(LatitudeLongitude( 61.141487,-140.657281));
    zone.push_back(LatitudeLongitude( 47.718672,-119.457813));
    zone.push_back(LatitudeLongitude( 40.227427,-123.824749));
    zone.push_back(LatitudeLongitude( 32.974717,-116.627637));
    zone.push_back(LatitudeLongitude( 32.535000,-117.101833)); // Polygon needs to be closed
    // Then build a PointInCartesianPolygon object
    const PointInCartesianPolygon eca(zone);
//! [PointInCartesianPolygonTest example]
//! [PointInCartesianPolygonTest expected output]
    // This object can then be asked if a point is in the zone or not
    ASSERT_FALSE(eca.is_in_polygon(LatitudeLongitude(0,0)));
    //ASSERT_TRUE(eca.is_in_zone(LatitudeLongitude(35),-120));
    ASSERT_TRUE(eca.is_in_polygon(LatitudeLongitude(40,-126)));
//! [PointInCartesianPolygonTest expected output]
}

TEST_F(PointInCartesianPolygonTest, simple_triangle_example)
{
    std::vector<LatitudeLongitude> zone;
    zone.push_back(LatitudeLongitude(0,0));
    zone.push_back(LatitudeLongitude(0,80));
    zone.push_back(LatitudeLongitude(40,40));
    zone.push_back(LatitudeLongitude(0,0));

    const PointInCartesianPolygon eca(zone);

    ASSERT_TRUE(eca.is_in_polygon(LatitudeLongitude(20,40)));
    ASSERT_TRUE(eca.is_in_polygon(LatitudeLongitude(10,15)));
    ASSERT_FALSE(eca.is_in_polygon(LatitudeLongitude(20,16.1)));
    ASSERT_TRUE(eca.is_in_polygon(LatitudeLongitude(18.98,23)));
    ASSERT_TRUE(eca.is_in_polygon(LatitudeLongitude(18.975,23)));
    ASSERT_TRUE(eca.is_in_polygon(LatitudeLongitude(18.97,23)));
    ASSERT_TRUE(eca.is_in_polygon(LatitudeLongitude(16.2,20)));
    ASSERT_TRUE(eca.is_in_polygon(LatitudeLongitude(16.19,20)));
    ASSERT_TRUE(eca.is_in_polygon(LatitudeLongitude(16.185,20)));
}

TEST_F(PointInCartesianPolygonTest, constructor_should_throw_if_received_less_than_three_points)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        std::vector<LatitudeLongitude> zone;
        ASSERT_THROW(PointInCartesianPolygon p1(zone), PointInPolygonException);
        zone.push_back(a.random<LatitudeLongitude>());
        ASSERT_THROW(PointInCartesianPolygon p2(zone), PointInPolygonException);
        zone.push_back(a.random<LatitudeLongitude>());
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
        std::vector<LatitudeLongitude> zone = a.random_vector_of<LatitudeLongitude>().of_size(n);
        ASSERT_THROW(PointInCartesianPolygon p1(zone), PointInPolygonException);
        zone.push_back(zone.front());
        ASSERT_NO_THROW(PointInCartesianPolygon p2(zone));
    }
}
