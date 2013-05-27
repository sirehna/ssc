/*
 * PointInGeographicalPolygonTest.cpp
 *
 * \date 27 mars 2013, 16:10:22
 *  \author cec
 */

#include "PointInGeographicalPolygonTest.hpp"
#include "PointInGeographicalPolygon.hpp"
#include "LatitudeLongitudeGenerators.hpp"
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
    // Then build a PointInGeographicalPolygon object
    const PointInGeographicalPolygon eca(zone);
//! [PointInGeographicalPolygonTest example]
//! [PointInGeographicalPolygonTest expected output]
    // This object can then be asked if a point is in the zone or not
    ASSERT_FALSE(eca.is_in_polygon(LatitudeLongitude(0,0)));
    ASSERT_TRUE(eca.is_in_polygon(LatitudeLongitude(40,-126)));
//! [PointInGeographicalPolygonTest expected output]
}

TEST_F(PointInGeographicalPolygonTest, known_limitation_does_not_work_for_north_pole)
{
    std::vector<LatitudeLongitude> zone;

    zone.push_back(LatitudeLongitude(60,0));
    zone.push_back(LatitudeLongitude(60,-90));
    zone.push_back(LatitudeLongitude(60,180));
    zone.push_back(LatitudeLongitude(60,90));
    zone.push_back(LatitudeLongitude(90,0));
    zone.push_back(LatitudeLongitude(60,0));
    const PointInGeographicalPolygon eca(zone);
    ASSERT_FALSE(eca.is_in_polygon(LatitudeLongitude(90,0)));
}


TEST_F(PointInGeographicalPolygonTest, simple_triangle_example)
{
    std::vector<LatitudeLongitude> zone;
    zone.push_back(LatitudeLongitude(0,0));
    zone.push_back(LatitudeLongitude(0,80));
    zone.push_back(LatitudeLongitude(40,40));
    zone.push_back(LatitudeLongitude(0,0));

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
        std::vector<LatitudeLongitude> zone;
        ASSERT_THROW(PointInGeographicalPolygon p1(zone), PointInPolygonException);
        zone.push_back(a.random<LatitudeLongitude>());
        ASSERT_THROW(PointInGeographicalPolygon p2(zone), PointInPolygonException);
        zone.push_back(a.random<LatitudeLongitude>());
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
        std::vector<LatitudeLongitude> zone = a.random_vector_of<LatitudeLongitude>().of_size(n);
        ASSERT_THROW(PointInGeographicalPolygon p1(zone), PointInPolygonException);
        zone.push_back(zone.front());
        ASSERT_NO_THROW(PointInGeographicalPolygon p2(zone));
    }
}
