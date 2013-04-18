/*
 * PointInGeographicalPolygonTest.cpp
 *
 * \date 27 mars 2013, 16:10:22
 *  \author cec
 */

#include "PointInGeographicalPolygonTest.hpp"
#include "PointInGeographicalPolygon.hpp"
#include "LongitudeLatitudeGenerators.hpp"
#include "LatitudeOfPointOnBorder.hpp"

#define EPS 1e-6

PointInGeographicalPolygonTest::PointInGeographicalPolygonTest() : a(DataGenerator(997788))
{
}

PointInGeographicalPolygonTest::~PointInGeographicalPolygonTest()
{
}

void PointInGeographicalPolygonTest::SetUp()
{
}

void PointInGeographicalPolygonTest::TearDown()
{
}

TEST_F(PointInGeographicalPolygonTest, example)
{
//! [PointInGeographicalPolygonTest example]
    // Start by declaring an ECA zone
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
    // Then build a PointInGeographicalPolygon object
    const PointInGeographicalPolygon eca(zone);
//! [PointInGeographicalPolygonTest example]
//! [PointInGeographicalPolygonTest expected output]
    // This object can then be asked if a point is in the zone or not
    ASSERT_FALSE(eca.is_in_polygon(LongitudeLatitude(0,0)));
    ASSERT_TRUE(eca.is_in_polygon(LongitudeLatitude(-126,40)));
//! [PointInGeographicalPolygonTest expected output]
}

TEST_F(PointInGeographicalPolygonTest, known_limitation_does_not_work_for_north_pole)
{
    std::vector<LongitudeLatitude> zone;

    zone.push_back(LongitudeLatitude(0,60));
    zone.push_back(LongitudeLatitude(-90,60));
    zone.push_back(LongitudeLatitude(180,60));
    zone.push_back(LongitudeLatitude(90,60));
    zone.push_back(LongitudeLatitude(0,90));
    zone.push_back(LongitudeLatitude(0,60));
    const PointInGeographicalPolygon eca(zone);
    ASSERT_FALSE(eca.is_in_polygon(LongitudeLatitude(0,90)));
}


TEST_F(PointInGeographicalPolygonTest, simple_triangle_example)
{
    std::vector<LongitudeLatitude> zone;
    zone.push_back(LongitudeLatitude(0,0));
    zone.push_back(LongitudeLatitude(80,0));
    zone.push_back(LongitudeLatitude(40,40));
    zone.push_back(LongitudeLatitude(0,0));

    const PointInGeographicalPolygon eca(zone);
    const LatitudeOfPointOnBorder g(new PointInGeographicalPolygon(eca),1e-10);

    ASSERT_NEAR(g.get_latitude(1),1.31666666666781750910,EPS);
    ASSERT_NEAR(g.get_latitude(2),2.61666666663837421680,EPS);
    ASSERT_NEAR(g.get_latitude(3),3.91666666668169050070,EPS);
    ASSERT_NEAR(g.get_latitude(4),5.21666666665224632030,EPS);
    ASSERT_NEAR(g.get_latitude(5),6.49999999998916244690,EPS);
    ASSERT_NEAR(g.get_latitude(6),7.78333333332607857360,EPS);
    ASSERT_NEAR(g.get_latitude(7),9.05000000002935323100,EPS);
    ASSERT_NEAR(g.get_latitude(8),10.3000000000262303960,EPS);
    ASSERT_NEAR(g.get_latitude(9),11.5500000000231040080,EPS);
    ASSERT_NEAR(g.get_latitude(10),12.783333333313578350,EPS);
    ASSERT_NEAR(g.get_latitude(11),13.999999999970413000,EPS);
    ASSERT_NEAR(g.get_latitude(12),15.199999999993604405,EPS);
    ASSERT_NEAR(g.get_latitude(13),16.366666666676756847,EPS);
    ASSERT_NEAR(g.get_latitude(14),17.533333333359912842,EPS);
    ASSERT_NEAR(g.get_latitude(15),18.683333333336662463,EPS);
    ASSERT_NEAR(g.get_latitude(16),19.799999999973380227,EPS);
    ASSERT_NEAR(g.get_latitude(17),20.899999999976444087,EPS);
    ASSERT_NEAR(g.get_latitude(18),21.983333333345875360,EPS);
    ASSERT_NEAR(g.get_latitude(19),23.033333333302508095,EPS);
    ASSERT_NEAR(g.get_latitude(20),24.066666666698253607,EPS);
    ASSERT_NEAR(g.get_latitude(21),25.083333333314847380,EPS);
    ASSERT_NEAR(g.get_latitude(22),26.066666666664154661,EPS);
    ASSERT_NEAR(g.get_latitude(23),27.033333333307055568,EPS);
    ASSERT_NEAR(g.get_latitude(24),27.966666666682684195,EPS);
    ASSERT_NEAR(g.get_latitude(25),28.899999999985553245,EPS);
    ASSERT_NEAR(g.get_latitude(26),29.783333333314736535,EPS);
    ASSERT_NEAR(g.get_latitude(27),30.666666666643919825,EPS);
    ASSERT_NEAR(g.get_latitude(28),31.516666666633071259,EPS);
    ASSERT_NEAR(g.get_latitude(29),32.333333333354929096,EPS);
    ASSERT_NEAR(g.get_latitude(30),33.133333333297628087,EPS);
    ASSERT_NEAR(g.get_latitude(31),33.916666666679446962,EPS);
    ASSERT_NEAR(g.get_latitude(32),34.683333333354866568,EPS);
    ASSERT_NEAR(g.get_latitude(33),35.416666666690261422,EPS);
    ASSERT_NEAR(g.get_latitude(34),36.133333333319242797,EPS);
    ASSERT_NEAR(g.get_latitude(35),36.833333333314584479,EPS);
    ASSERT_NEAR(g.get_latitude(36),37.499999999969872988,EPS);
    ASSERT_NEAR(g.get_latitude(37),38.166666666697921073,EPS);
    ASSERT_NEAR(g.get_latitude(38),38.800000000013184831,EPS);
}

TEST_F(PointInGeographicalPolygonTest, constructor_should_throw_if_received_less_than_three_points)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        std::vector<LongitudeLatitude> zone;
        ASSERT_THROW(PointInGeographicalPolygon p1(zone), PointInPolygonException);
        zone.push_back(a.random<LongitudeLatitude>());
        ASSERT_THROW(PointInGeographicalPolygon p2(zone), PointInPolygonException);
        zone.push_back(a.random<LongitudeLatitude>());
        ASSERT_THROW(PointInGeographicalPolygon p3(zone), PointInPolygonException);
        zone.push_back(zone.front());
        ASSERT_NO_THROW(PointInGeographicalPolygon p4(zone));
    }
}

TEST_F(PointInGeographicalPolygonTest, constructor_should_throw_if_polygon_is_not_closed)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(3,200);
        std::vector<LongitudeLatitude> zone = a.random_vector_of<LongitudeLatitude>().of_size(n);
        ASSERT_THROW(PointInGeographicalPolygon p1(zone), PointInPolygonException);
        zone.push_back(zone.front());
        ASSERT_NO_THROW(PointInGeographicalPolygon p2(zone));
    }
}
