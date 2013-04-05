/*
 * PointInSphericalPolygonTest.cpp
 *
 * \date 27 mars 2013, 16:10:38
 *  \author cec
 */

#include "PointInSphericalPolygonTest.hpp"
#include "PointInSphericalPolygon.hpp"
#include "LongitudeLatitudeGenerators.hpp"
#include "LatitudeOfPointOnBorder.hpp"

#define EPS 1e-6

PointInSphericalPolygonTest::PointInSphericalPolygonTest() : a(DataGenerator(997788))
{
}

PointInSphericalPolygonTest::~PointInSphericalPolygonTest()
{
}

void PointInSphericalPolygonTest::SetUp()
{
}

void PointInSphericalPolygonTest::TearDown()
{
}

TEST_F(PointInSphericalPolygonTest, example)
{
//! [PointInSphericalPolygonTest example]
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
    // Then build a PointInSphericalPolygon object
    PointInSphericalPolygon eca(zone);
//! [PointInSphericalPolygonTest example]
//! [PointInSphericalPolygonTest expected output]
    // This object can then be asked if a point is in the zone or not
    ASSERT_FALSE(eca.is_in_polygon(LongitudeLatitude(0,0)));
    //ASSERT_TRUE(eca.is_in_zone(LatitudeLongitude(-120,35)));
    ASSERT_TRUE(eca.is_in_polygon(LongitudeLatitude(-126,40)));
//! [PointInSphericalPolygonTest expected output]
}

TEST_F(PointInSphericalPolygonTest, known_limitation_does_not_work_for_north_pole)
{
    std::vector<LongitudeLatitude> zone;
    zone.push_back(LongitudeLatitude(0,60));
    zone.push_back(LongitudeLatitude(-90,60));
    zone.push_back(LongitudeLatitude(180,60));
    zone.push_back(LongitudeLatitude(90,60));
    zone.push_back(LongitudeLatitude(0,90));
    zone.push_back(LongitudeLatitude(0,60));
    PointInSphericalPolygon eca(zone);
    ASSERT_FALSE(eca.is_in_polygon(LongitudeLatitude(0,90)));
}

TEST_F(PointInSphericalPolygonTest, simple_triangle_example)
{
    std::vector<LongitudeLatitude> zone;
    zone.push_back(LongitudeLatitude(0,0));
    zone.push_back(LongitudeLatitude(80,0));
    zone.push_back(LongitudeLatitude(40,40));
    zone.push_back(LongitudeLatitude(0,0));


    PointInSphericalPolygon eca(zone);

    const LatitudeOfPointOnBorder g(new PointInSphericalPolygon(eca),1e-10);

    ASSERT_NEAR( 1.305115226733623, g.get_latitude(1), EPS);
    ASSERT_NEAR( 2.608480699373139, g.get_latitude(2), EPS);
    ASSERT_NEAR( 3.908359318802716, g.get_latitude(3), EPS);
    ASSERT_NEAR( 5.203038939139679, g.get_latitude(4), EPS);
    ASSERT_NEAR( 6.490844373560162, g.get_latitude(5), EPS);
    ASSERT_NEAR( 7.770148597531327, g.get_latitude(6), EPS);
    ASSERT_NEAR( 9.039383244199193, g.get_latitude(7), EPS);
    ASSERT_NEAR(10.297048063017346, g.get_latitude(8), EPS);
    ASSERT_NEAR(11.541719123600265, g.get_latitude(9), EPS);
    ASSERT_NEAR(12.772056096791351, g.get_latitude(10), EPS);
    ASSERT_NEAR(13.986807453019694, g.get_latitude(11), EPS);
    ASSERT_NEAR(15.184815862168833, g.get_latitude(12), EPS);
    ASSERT_NEAR(16.365021035928269, g.get_latitude(13), EPS);
    ASSERT_NEAR(17.526460612438054, g.get_latitude(14), EPS);
    ASSERT_NEAR(18.668273419447900, g.get_latitude(15), EPS);
    ASSERT_NEAR(19.789695470846393, g.get_latitude(16), EPS);
    ASSERT_NEAR(20.890062438274665, g.get_latitude(17), EPS);
    ASSERT_NEAR(21.968804687248650, g.get_latitude(18), EPS);
    ASSERT_NEAR(23.025445089177559, g.get_latitude(19), EPS);
    ASSERT_NEAR(24.059595603484880, g.get_latitude(20), EPS);
    ASSERT_NEAR(25.070950933763811, g.get_latitude(21), EPS);
    ASSERT_NEAR(26.059288291917216, g.get_latitude(22), EPS);
    ASSERT_NEAR(27.024457554230061, g.get_latitude(23), EPS);
}

TEST_F(PointInSphericalPolygonTest, constructor_should_throw_if_received_less_than_three_points)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        std::vector<LongitudeLatitude> zone;
        ASSERT_THROW(PointInSphericalPolygon p1(zone), PointInPolygonException);
        zone.push_back(a.random<LongitudeLatitude>());
        ASSERT_THROW(PointInSphericalPolygon p2(zone), PointInPolygonException);
        zone.push_back(a.random<LongitudeLatitude>());
        ASSERT_THROW(PointInSphericalPolygon p3(zone), PointInPolygonException);
        zone.push_back(zone.front());
        ASSERT_NO_THROW(PointInSphericalPolygon p4(zone));
    }
}

TEST_F(PointInSphericalPolygonTest, constructor_should_throw_if_polygon_is_not_closed)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const size_t n = a.random<size_t>().between(3,200);
        std::vector<LongitudeLatitude> zone = a.random_vector_of<LongitudeLatitude>().of_size(n);
        ASSERT_THROW(PointInSphericalPolygon p1(zone), PointInPolygonException);
        zone.push_back(zone.front());
        ASSERT_NO_THROW(PointInSphericalPolygon p2(zone));
    }
}
