/*
 * PointInGeographicalPolygonTest.cpp
 *
 * \date 27 mars 2013, 16:10:22
 * \author cec
 */

#include "PointInGeographicalPolygonTest.hpp"
#include "LatitudeLongitudeGenerators.hpp"
#include "LatitudeOfPointOnBorder.hpp"
#include "ssc/geometry/PointInGeographicalPolygon.hpp"
#include "ssc/geometry/PointInSphericalPolygon.hpp"
#include "ssc/geometry/PointInCartesianPolygon.hpp"

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/extensions/gis/latlong/latlong.hpp>

#include <algorithm> // std::reverse
#define EPS 1e-6

using namespace ssc::geometry;

PointInGeographicalPolygonTest::PointInGeographicalPolygonTest() : a(ssc::random_data_generator::DataGenerator(997788))
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

TEST_F(PointInGeographicalPolygonTest, bug)
{
    std::vector<LatitudeLongitude> zone;
    zone.push_back(LatitudeLongitude(60,-64.156));
    zone.push_back(LatitudeLongitude(60,-56.71666667));
    zone.push_back(LatitudeLongitude(58.90016667,-55.63416667));
    zone.push_back(LatitudeLongitude(57.842,-55.05783333));
    zone.push_back(LatitudeLongitude(57.5855,-54.00983333));
    zone.push_back(LatitudeLongitude(57.23666667,-53.12633333));
    zone.push_back(LatitudeLongitude(56.8015,-52.38816667));
    zone.push_back(LatitudeLongitude(56.30216667,-51.82366667));
    zone.push_back(LatitudeLongitude(54.38683333,-50.29066667));
    zone.push_back(LatitudeLongitude(53.74233333,-50.1195));
    zone.push_back(LatitudeLongitude(53.0765,-50.1675));
    zone.push_back(LatitudeLongitude(52.33433333,-49.9515));
    zone.push_back(LatitudeLongitude(51.57,-48.87416667));
    zone.push_back(LatitudeLongitude(50.66916667,-48.26733333));
    zone.push_back(LatitudeLongitude(50.038,-48.11716667));
    zone.push_back(LatitudeLongitude(49.4005,-48.15583333));
    zone.push_back(LatitudeLongitude(48.65366667,-47.9195));
    zone.push_back(LatitudeLongitude(47.40416667,-47.776));
    zone.push_back(LatitudeLongitude(46.58533333,-48.009));
    zone.push_back(LatitudeLongitude(45.32416667,-48.72133333));
    zone.push_back(LatitudeLongitude(44.723,-49.275));
    zone.push_back(LatitudeLongitude(44.273,-49.85383333));
    zone.push_back(LatitudeLongitude(43.88583333,-50.56683333));
    zone.push_back(LatitudeLongitude(43.601,-51.34016667));
    zone.push_back(LatitudeLongitude(43.39316667,-52.287));
    zone.push_back(LatitudeLongitude(43.325,-53.3355));
    zone.push_back(LatitudeLongitude(43.35233333,-54.15333333));
    zone.push_back(LatitudeLongitude(43.49016667,-55.1235));
    zone.push_back(LatitudeLongitude(42.66866667,-55.524));
    zone.push_back(LatitudeLongitude(41.96983333,-56.15566667));
    zone.push_back(LatitudeLongitude(41.33683333,-57.0855));
    zone.push_back(LatitudeLongitude(40.92233333,-58.0425));
    zone.push_back(LatitudeLongitude(40.68966667,-59.08633333));
    zone.push_back(LatitudeLongitude(40.63883333,-60.20333333));
    zone.push_back(LatitudeLongitude(40.75766667,-61.23383333));
    zone.push_back(LatitudeLongitude(41.07533333,-62.2915));
    zone.push_back(LatitudeLongitude(40.60916667,-63.17483333));
    zone.push_back(LatitudeLongitude(40.28866667,-64.1395));
    zone.push_back(LatitudeLongitude(40.12433333,-64.9885));
    zone.push_back(LatitudeLongitude(40.09066667,-65.8845));
    zone.push_back(LatitudeLongitude(39.9675,-65.99183333));
    zone.push_back(LatitudeLongitude(39.47066667,-66.35233333));
    zone.push_back(LatitudeLongitude(39.02566667,-66.8055));
    zone.push_back(LatitudeLongitude(38.65266667,-67.34316667));
    zone.push_back(LatitudeLongitude(38.32,-68.0335));
    zone.push_back(LatitudeLongitude(38.08816667,-68.77583333));
    zone.push_back(LatitudeLongitude(37.969,-69.56783333));
    zone.push_back(LatitudeLongitude(37.95783333,-70.4015));
    zone.push_back(LatitudeLongitude(37.87433333,-70.625));
    zone.push_back(LatitudeLongitude(37.30616667,-71.13883333));
    zone.push_back(LatitudeLongitude(36.5375,-71.55983333));
    zone.push_back(LatitudeLongitude(35.57633333,-71.43366667));
    zone.push_back(LatitudeLongitude(34.55166667,-71.61733333));
    zone.push_back(LatitudeLongitude(33.90816667,-71.8725));
    zone.push_back(LatitudeLongitude(33.3205,-72.28533333));
    zone.push_back(LatitudeLongitude(32.75516667,-72.90083333));
    zone.push_back(LatitudeLongitude(31.91883333,-74.20033333));
    zone.push_back(LatitudeLongitude(31.45233333,-75.25333333));
    zone.push_back(LatitudeLongitude(31.05266667,-75.853));
    zone.push_back(LatitudeLongitude(30.757,-76.523));
    zone.push_back(LatitudeLongitude(30.208,-77.30483333));
    zone.push_back(LatitudeLongitude(29.4195,-76.94033333));
    zone.push_back(LatitudeLongitude(28.60983333,-76.79333333));
    zone.push_back(LatitudeLongitude(28.2855,-76.66833333));
    zone.push_back(LatitudeLongitude(28.28533333,-79.18716667));
    zone.push_back(LatitudeLongitude(27.876,-79.4725));
    zone.push_back(LatitudeLongitude(27.4335,-79.523));
    zone.push_back(LatitudeLongitude(27.26883333,-79.56966667));
    zone.push_back(LatitudeLongitude(27.19233333,-79.576));
    zone.push_back(LatitudeLongitude(27.09316667,-79.5865));
    zone.push_back(LatitudeLongitude(27.00466667,-79.58616667));
    zone.push_back(LatitudeLongitude(26.91933333,-79.57316667));
    zone.push_back(LatitudeLongitude(26.893,-79.57116667));
    zone.push_back(LatitudeLongitude(26.75766667,-79.54016667));
    zone.push_back(LatitudeLongitude(26.73833333,-79.53716667));
    zone.push_back(LatitudeLongitude(26.72333333,-79.53666667));
    zone.push_back(LatitudeLongitude(26.68533333,-79.5335));
    zone.push_back(LatitudeLongitude(26.6355,-79.522));
    zone.push_back(LatitudeLongitude(26.605,-79.51766667));
    zone.push_back(LatitudeLongitude(26.58683333,-79.50833333));
    zone.push_back(LatitudeLongitude(26.57516667,-79.50766667));
    zone.push_back(LatitudeLongitude(26.5685,-79.50633333));
    zone.push_back(LatitudeLongitude(26.51866667,-79.5025));
    zone.push_back(LatitudeLongitude(26.48416667,-79.49216667));
    zone.push_back(LatitudeLongitude(26.42183333,-79.493));
    zone.push_back(LatitudeLongitude(26.38816667,-79.4925));
    zone.push_back(LatitudeLongitude(26.38683333,-79.49233333));
    zone.push_back(LatitudeLongitude(26.3095,-79.52583333));
    zone.push_back(LatitudeLongitude(26.25433333,-79.55283333));
    zone.push_back(LatitudeLongitude(26.25216667,-79.55383333));
    zone.push_back(LatitudeLongitude(26.13483333,-79.59216667));
    zone.push_back(LatitudeLongitude(26.1245,-79.6015));
    zone.push_back(LatitudeLongitude(26.10983333,-79.60583333));
    zone.push_back(LatitudeLongitude(26.042,-79.637));
    zone.push_back(LatitudeLongitude(25.98833333,-79.66716667));
    zone.push_back(LatitudeLongitude(25.986,-79.668));
    zone.push_back(LatitudeLongitude(25.958,-79.673));
    zone.push_back(LatitudeLongitude(25.93633333,-79.68433333));
    zone.push_back(LatitudeLongitude(25.90066667,-79.68966667));
    zone.push_back(LatitudeLongitude(25.88733333,-79.691));
    zone.push_back(LatitudeLongitude(25.859,-79.69316667));
    zone.push_back(LatitudeLongitude(25.82216667,-79.70266667));
    zone.push_back(LatitudeLongitude(25.804,-79.70383333));
    zone.push_back(LatitudeLongitude(25.80333333,-79.704));
    zone.push_back(LatitudeLongitude(25.771,-79.70733333));
    zone.push_back(LatitudeLongitude(25.76933333,-79.7075));
    zone.push_back(LatitudeLongitude(25.72333333,-79.70983333));
    zone.push_back(LatitudeLongitude(25.70516667,-79.708));
    zone.push_back(LatitudeLongitude(25.67283333,-79.7045));
    zone.push_back(LatitudeLongitude(25.62066667,-79.7045));
    zone.push_back(LatitudeLongitude(25.618,-79.7045));
    zone.push_back(LatitudeLongitude(25.51716667,-79.702));
    zone.push_back(LatitudeLongitude(25.45983333,-79.70183333));
    zone.push_back(LatitudeLongitude(25.40066667,-79.702));
    zone.push_back(LatitudeLongitude(25.37016667,-79.70333333));
    zone.push_back(LatitudeLongitude(25.35483333,-79.70133333));
    zone.push_back(LatitudeLongitude(25.27533333,-79.68733333));
    zone.push_back(LatitudeLongitude(25.2595,-79.6885));
    zone.push_back(LatitudeLongitude(25.17316667,-79.6885));
    zone.push_back(LatitudeLongitude(25.1585,-79.68933333));
    zone.push_back(LatitudeLongitude(25.1505,-79.69083333));
    zone.push_back(LatitudeLongitude(25.05916667,-79.70483333));
    zone.push_back(LatitudeLongitude(25.04333333,-79.70933333));
    zone.push_back(LatitudeLongitude(25.005,-79.73416667));
    zone.push_back(LatitudeLongitude(24.98383333,-79.74133333));
    zone.push_back(LatitudeLongitude(24.92133333,-79.7595));
    zone.push_back(LatitudeLongitude(24.73633333,-79.82066667));
    zone.push_back(LatitudeLongitude(24.71733333,-79.823));
    zone.push_back(LatitudeLongitude(24.706,-79.84166667));
    zone.push_back(LatitudeLongitude(24.69116667,-79.87616667));
    zone.push_back(LatitudeLongitude(24.63866667,-79.993));
    zone.push_back(LatitudeLongitude(24.6045,-80.0585));
    zone.push_back(LatitudeLongitude(24.553,-80.20716667));
    zone.push_back(LatitudeLongitude(24.55083333,-80.22016667));
    zone.push_back(LatitudeLongitude(24.5355,-80.25266667));
    zone.push_back(LatitudeLongitude(24.52116667,-80.27583333));
    zone.push_back(LatitudeLongitude(24.5095,-80.29116667));
    zone.push_back(LatitudeLongitude(24.50233333,-80.32016667));
    zone.push_back(LatitudeLongitude(24.501,-80.324));
    zone.push_back(LatitudeLongitude(24.48966667,-80.35083333));
    zone.push_back(LatitudeLongitude(24.46966667,-80.40583333));
    zone.push_back(LatitudeLongitude(24.46766667,-80.41833333));
    zone.push_back(LatitudeLongitude(24.45383333,-80.45333333));
    zone.push_back(LatitudeLongitude(24.43833333,-80.48833333));
    zone.push_back(LatitudeLongitude(24.41783333,-80.537));
    zone.push_back(LatitudeLongitude(24.38833333,-80.6015));
    zone.push_back(LatitudeLongitude(24.37216667,-80.64266667));
    zone.push_back(LatitudeLongitude(24.36783333,-80.6585));
    zone.push_back(LatitudeLongitude(24.32183333,-80.7535));
    zone.push_back(LatitudeLongitude(24.31933333,-80.75783333));
    zone.push_back(LatitudeLongitude(24.30633333,-80.77483333));
    zone.push_back(LatitudeLongitude(24.30583333,-80.77566667));
    zone.push_back(LatitudeLongitude(24.1585,-80.99116667));
    zone.push_back(LatitudeLongitude(24.158,-80.99183333));
    zone.push_back(LatitudeLongitude(24.143,-81.01783333));
    zone.push_back(LatitudeLongitude(24.13833333,-81.02516667));
    zone.push_back(LatitudeLongitude(24.13766667,-81.02616667));
    zone.push_back(LatitudeLongitude(24.12133333,-81.051));
    zone.push_back(LatitudeLongitude(24.03666667,-81.15083333));
    zone.push_back(LatitudeLongitude(23.99333333,-81.186));
    zone.push_back(LatitudeLongitude(23.922,-81.20916667));
    zone.push_back(LatitudeLongitude(23.892,-81.32383333));
    zone.push_back(LatitudeLongitude(23.842,-81.49316667));
    zone.push_back(LatitudeLongitude(23.83366667,-81.65983333));
    zone.push_back(LatitudeLongitude(23.8175,-81.8265));
    zone.push_back(LatitudeLongitude(23.8175,-82.00183333));
    zone.push_back(LatitudeLongitude(23.82366667,-82.15983333));
    zone.push_back(LatitudeLongitude(23.85233333,-82.40983333));
    zone.push_back(LatitudeLongitude(23.85233333,-82.65983333));
    zone.push_back(LatitudeLongitude(23.82366667,-82.80883333));
    zone.push_back(LatitudeLongitude(23.822,-82.85183333));
    zone.push_back(LatitudeLongitude(23.82066667,-82.99316667));
    zone.push_back(LatitudeLongitude(23.82533333,-83.24316667));
    zone.push_back(LatitudeLongitude(23.85366667,-83.42483333));
    zone.push_back(LatitudeLongitude(23.87116667,-83.55016667));
    zone.push_back(LatitudeLongitude(23.90066667,-83.68916667));
    zone.push_back(LatitudeLongitude(23.9245,-83.80183333));
    zone.push_back(LatitudeLongitude(23.973,-83.99316667));
    zone.push_back(LatitudeLongitude(24.15616667,-84.48783333));
    zone.push_back(LatitudeLongitude(24.22,-84.63983333));
    zone.push_back(LatitudeLongitude(24.2735,-84.76783333));
    zone.push_back(LatitudeLongitude(24.38833333,-84.99316667));
    zone.push_back(LatitudeLongitude(24.4395,-85.10316667));
    zone.push_back(LatitudeLongitude(24.64283333,-85.52566667));
    zone.push_back(LatitudeLongitude(24.73616667,-85.7185));
    zone.push_back(LatitudeLongitude(24.89283333,-85.99316667));
    zone.push_back(LatitudeLongitude(25.174,-86.50116667));
    zone.push_back(LatitudeLongitude(25.71916667,-86.35233333));
    zone.push_back(LatitudeLongitude(26.21883333,-86.1075));
    zone.push_back(LatitudeLongitude(26.45366667,-86.21916667));
    zone.push_back(LatitudeLongitude(26.55766667,-86.61783333));
    zone.push_back(LatitudeLongitude(26.02066667,-87.48916667));
    zone.push_back(LatitudeLongitude(25.70416667,-88.55));
    zone.push_back(LatitudeLongitude(25.77566667,-90.49016667));
    zone.push_back(LatitudeLongitude(25.73983333,-90.78416667));
    zone.push_back(LatitudeLongitude(25.85716667,-91.875));
    zone.push_back(LatitudeLongitude(26.29066667,-93.05983333));
    zone.push_back(LatitudeLongitude(25.9925,-93.55866667));
    zone.push_back(LatitudeLongitude(26.00533333,-95.6545));
    zone.push_back(LatitudeLongitude(26.0055,-96.805));
    zone.push_back(LatitudeLongitude(25.972,-96.92133333));
    zone.push_back(LatitudeLongitude(25.96916667,-96.9735));
    zone.push_back(LatitudeLongitude(25.95966667,-97.02566667));
    zone.push_back(LatitudeLongitude(25.95683333,-97.08466667));
    zone.push_back(LatitudeLongitude(25.954,-97.13683333));
    zone.push_back(LatitudeLongitude(25.954,-97.14116667));
    zone.push_back(LatitudeLongitude(27.01607612255437,-97.81605295593207));
    zone.push_back(LatitudeLongitude(35.3356681601088,-91.76985060722265));
    zone.push_back(LatitudeLongitude(41.0738644453726,-84.89571294528193));
    zone.push_back(LatitudeLongitude(54.64100005535186,-70.34043050675062));
    zone.push_back(LatitudeLongitude(60,-64.156));

    std::reverse(zone.begin(),zone.end());

    const PointInCartesianPolygon eca_car(zone);
    const PointInSphericalPolygon eca_sph(zone);
    const PointInGeographicalPolygon eca_geo(zone);
    const LatitudeLongitude p_in(30,-80);
    const LatitudeLongitude p_out_ko(25.9556,-78.1239);
    const LatitudeLongitude p_out_ok(25.95,-78.1239);

    ASSERT_TRUE(eca_car.is_in_polygon(p_in));
    ASSERT_FALSE(eca_car.is_in_polygon(p_out_ok));
    ASSERT_FALSE(eca_car.is_in_polygon(p_out_ko));

    ASSERT_TRUE(eca_sph.is_in_polygon(p_in));

    ASSERT_TRUE(eca_geo.is_in_polygon(p_in));

    ASSERT_FALSE(eca_sph.is_in_polygon(p_out_ok));
    ASSERT_FALSE(eca_geo.is_in_polygon(p_out_ok));
    //ASSERT_FALSE(eca_sph.is_in_polygon(p_out_ko));
    //ASSERT_FALSE(eca_geo.is_in_polygon(p_out_ko));
}

boost::geometry::model::point<double, 2, boost::geometry::cs::spherical_equatorial<boost::geometry::degree> > convert(const double longitude, const double latitude);
boost::geometry::model::point<double, 2, boost::geometry::cs::spherical_equatorial<boost::geometry::degree> > convert(const double longitude, const double latitude)
{
    return boost::geometry::model::point<double, 2, boost::geometry::cs::spherical_equatorial<boost::geometry::degree> >(longitude,latitude);
}

typedef boost::geometry::model::point<double, 2, boost::geometry::cs::spherical_equatorial<boost::geometry::degree> > PointType;


TEST_F(PointInGeographicalPolygonTest, DISABLED_boost_bug_report_9354)
{
    boost::geometry::model::polygon<PointType> polygon;
    boost::geometry::append(polygon, convert(-64.156,60));
    boost::geometry::append(polygon, convert(-56.71666667,60));
    boost::geometry::append(polygon, convert(-55.63416667,58.90016667));
    boost::geometry::append(polygon, convert(-55.05783333,57.842));
    boost::geometry::append(polygon, convert(-54.00983333,57.5855));
    boost::geometry::append(polygon, convert(-53.12633333,57.23666667));
    boost::geometry::append(polygon, convert(-52.38816667,56.8015));
    boost::geometry::append(polygon, convert(-51.82366667,56.30216667));
    boost::geometry::append(polygon, convert(-50.29066667,54.38683333));
    boost::geometry::append(polygon, convert(-50.1195,53.74233333));
    boost::geometry::append(polygon, convert(-50.1675,53.0765));
    boost::geometry::append(polygon, convert(-49.9515,52.33433333));
    boost::geometry::append(polygon, convert(-48.87416667,51.57));
    boost::geometry::append(polygon, convert(-48.26733333,50.66916667));
    boost::geometry::append(polygon, convert(-48.11716667,50.038));
    boost::geometry::append(polygon, convert(-48.15583333,49.4005));
    boost::geometry::append(polygon, convert(-47.9195,48.65366667));
    boost::geometry::append(polygon, convert(-47.776,47.40416667));
    boost::geometry::append(polygon, convert(-48.009,46.58533333));
    boost::geometry::append(polygon, convert(-48.72133333,45.32416667));
    boost::geometry::append(polygon, convert(-49.275,44.723));
    boost::geometry::append(polygon, convert(-49.85383333,44.273));
    boost::geometry::append(polygon, convert(-50.56683333,43.88583333));
    boost::geometry::append(polygon, convert(-51.34016667,43.601));
    boost::geometry::append(polygon, convert(-52.287,43.39316667));
    boost::geometry::append(polygon, convert(-53.3355,43.325));
    boost::geometry::append(polygon, convert(-54.15333333,43.35233333));
    boost::geometry::append(polygon, convert(-55.1235,43.49016667));
    boost::geometry::append(polygon, convert(-55.524,42.66866667));
    boost::geometry::append(polygon, convert(-56.15566667,41.96983333));
    boost::geometry::append(polygon, convert(-57.0855,41.33683333));
    boost::geometry::append(polygon, convert(-58.0425,40.92233333));
    boost::geometry::append(polygon, convert(-59.08633333,40.68966667));
    boost::geometry::append(polygon, convert(-60.20333333,40.63883333));
    boost::geometry::append(polygon, convert(-61.23383333,40.75766667));
    boost::geometry::append(polygon, convert(-62.2915,41.07533333));
    boost::geometry::append(polygon, convert(-63.17483333,40.60916667));
    boost::geometry::append(polygon, convert(-64.1395,40.28866667));
    boost::geometry::append(polygon, convert(-64.9885,40.12433333));
    boost::geometry::append(polygon, convert(-65.8845,40.09066667));
    boost::geometry::append(polygon, convert(-65.99183333,39.9675));
    boost::geometry::append(polygon, convert(-66.35233333,39.47066667));
    boost::geometry::append(polygon, convert(-66.8055,39.02566667));
    boost::geometry::append(polygon, convert(-67.34316667,38.65266667));
    boost::geometry::append(polygon, convert(-68.0335,38.32));
    boost::geometry::append(polygon, convert(-68.77583333,38.08816667));
    boost::geometry::append(polygon, convert(-69.56783333,37.969));
    boost::geometry::append(polygon, convert(-70.4015,37.95783333));
    boost::geometry::append(polygon, convert(-70.625,37.87433333));
    boost::geometry::append(polygon, convert(-71.13883333,37.30616667));
    boost::geometry::append(polygon, convert(-71.55983333,36.5375));
    boost::geometry::append(polygon, convert(-71.43366667,35.57633333));
    boost::geometry::append(polygon, convert(-71.61733333,34.55166667));
    boost::geometry::append(polygon, convert(-71.8725,33.90816667));
    boost::geometry::append(polygon, convert(-72.28533333,33.3205));
    boost::geometry::append(polygon, convert(-72.90083333,32.75516667));
    boost::geometry::append(polygon, convert(-74.20033333,31.91883333));
    boost::geometry::append(polygon, convert(-75.25333333,31.45233333));
    boost::geometry::append(polygon, convert(-75.853,31.05266667));
    boost::geometry::append(polygon, convert(-76.523,30.757));
    boost::geometry::append(polygon, convert(-77.30483333,30.208));
    boost::geometry::append(polygon, convert(-76.94033333,29.4195));
    boost::geometry::append(polygon, convert(-76.79333333,28.60983333));
    boost::geometry::append(polygon, convert(-76.66833333,28.2855));
    boost::geometry::append(polygon, convert(-79.18716667,28.28533333));
    boost::geometry::append(polygon, convert(-79.4725,27.876));
    boost::geometry::append(polygon, convert(-79.523,27.4335));
    boost::geometry::append(polygon, convert(-79.56966667,27.26883333));
    boost::geometry::append(polygon, convert(-79.576,27.19233333));
    boost::geometry::append(polygon, convert(-79.5865,27.09316667));
    boost::geometry::append(polygon, convert(-79.58616667,27.00466667));
    boost::geometry::append(polygon, convert(-79.57316667,26.91933333));
    boost::geometry::append(polygon, convert(-79.57116667,26.893));
    boost::geometry::append(polygon, convert(-79.54016667,26.75766667));
    boost::geometry::append(polygon, convert(-79.53716667,26.73833333));
    boost::geometry::append(polygon, convert(-79.53666667,26.72333333));
    boost::geometry::append(polygon, convert(-79.5335,26.68533333));
    boost::geometry::append(polygon, convert(-79.522,26.6355));
    boost::geometry::append(polygon, convert(-79.51766667,26.605));
    boost::geometry::append(polygon, convert(-79.50833333,26.58683333));
    boost::geometry::append(polygon, convert(-79.50766667,26.57516667));
    boost::geometry::append(polygon, convert(-79.50633333,26.5685));
    boost::geometry::append(polygon, convert(-79.5025,26.51866667));
    boost::geometry::append(polygon, convert(-79.49216667,26.48416667));
    boost::geometry::append(polygon, convert(-79.493,26.42183333));
    boost::geometry::append(polygon, convert(-79.4925,26.38816667));
    boost::geometry::append(polygon, convert(-79.49233333,26.38683333));
    boost::geometry::append(polygon, convert(-79.52583333,26.3095));
    boost::geometry::append(polygon, convert(-79.55283333,26.25433333));
    boost::geometry::append(polygon, convert(-79.55383333,26.25216667));
    boost::geometry::append(polygon, convert(-79.59216667,26.13483333));
    boost::geometry::append(polygon, convert(-79.6015,26.1245));
    boost::geometry::append(polygon, convert(-79.60583333,26.10983333));
    boost::geometry::append(polygon, convert(-79.637,26.042));
    boost::geometry::append(polygon, convert(-79.66716667,25.98833333));
    boost::geometry::append(polygon, convert(-79.668,25.986));
    boost::geometry::append(polygon, convert(-79.673,25.958));
    boost::geometry::append(polygon, convert(-79.68433333,25.93633333));
    boost::geometry::append(polygon, convert(-79.68966667,25.90066667));
    boost::geometry::append(polygon, convert(-79.691,25.88733333));
    boost::geometry::append(polygon, convert(-79.69316667,25.859));
    boost::geometry::append(polygon, convert(-79.70266667,25.82216667));
    boost::geometry::append(polygon, convert(-79.70383333,25.804));
    boost::geometry::append(polygon, convert(-79.704,25.80333333));
    boost::geometry::append(polygon, convert(-79.70733333,25.771));
    boost::geometry::append(polygon, convert(-79.7075,25.76933333));
    boost::geometry::append(polygon, convert(-79.70983333,25.72333333));
    boost::geometry::append(polygon, convert(-79.708,25.70516667));
    boost::geometry::append(polygon, convert(-79.7045,25.67283333));
    boost::geometry::append(polygon, convert(-79.7045,25.62066667));
    boost::geometry::append(polygon, convert(-79.7045,25.618));
    boost::geometry::append(polygon, convert(-79.702,25.51716667));
    boost::geometry::append(polygon, convert(-79.70183333,25.45983333));
    boost::geometry::append(polygon, convert(-79.702,25.40066667));
    boost::geometry::append(polygon, convert(-79.70333333,25.37016667));
    boost::geometry::append(polygon, convert(-79.70133333,25.35483333));
    boost::geometry::append(polygon, convert(-79.68733333,25.27533333));
    boost::geometry::append(polygon, convert(-79.6885,25.2595));
    boost::geometry::append(polygon, convert(-79.6885,25.17316667));
    boost::geometry::append(polygon, convert(-79.68933333,25.1585));
    boost::geometry::append(polygon, convert(-79.69083333,25.1505));
    boost::geometry::append(polygon, convert(-79.70483333,25.05916667));
    boost::geometry::append(polygon, convert(-79.70933333,25.04333333));
    boost::geometry::append(polygon, convert(-79.73416667,25.005));
    boost::geometry::append(polygon, convert(-79.74133333,24.98383333));
    boost::geometry::append(polygon, convert(-79.7595,24.92133333));
    boost::geometry::append(polygon, convert(-79.82066667,24.73633333));
    boost::geometry::append(polygon, convert(-79.823,24.71733333));
    boost::geometry::append(polygon, convert(-79.84166667,24.706));
    boost::geometry::append(polygon, convert(-79.87616667,24.69116667));
    boost::geometry::append(polygon, convert(-79.993,24.63866667));
    boost::geometry::append(polygon, convert(-80.0585,24.6045));
    boost::geometry::append(polygon, convert(-80.20716667,24.553));
    boost::geometry::append(polygon, convert(-80.22016667,24.55083333));
    boost::geometry::append(polygon, convert(-80.25266667,24.5355));
    boost::geometry::append(polygon, convert(-80.27583333,24.52116667));
    boost::geometry::append(polygon, convert(-80.29116667,24.5095));
    boost::geometry::append(polygon, convert(-80.32016667,24.50233333));
    boost::geometry::append(polygon, convert(-80.324,24.501));
    boost::geometry::append(polygon, convert(-80.35083333,24.48966667));
    boost::geometry::append(polygon, convert(-80.40583333,24.46966667));
    boost::geometry::append(polygon, convert(-80.41833333,24.46766667));
    boost::geometry::append(polygon, convert(-80.45333333,24.45383333));
    boost::geometry::append(polygon, convert(-80.48833333,24.43833333));
    boost::geometry::append(polygon, convert(-80.537,24.41783333));
    boost::geometry::append(polygon, convert(-80.6015,24.38833333));
    boost::geometry::append(polygon, convert(-80.64266667,24.37216667));
    boost::geometry::append(polygon, convert(-80.6585,24.36783333));
    boost::geometry::append(polygon, convert(-80.7535,24.32183333));
    boost::geometry::append(polygon, convert(-80.75783333,24.31933333));
    boost::geometry::append(polygon, convert(-80.77483333,24.30633333));
    boost::geometry::append(polygon, convert(-80.77566667,24.30583333));
    boost::geometry::append(polygon, convert(-80.99116667,24.1585));
    boost::geometry::append(polygon, convert(-80.99183333,24.158));
    boost::geometry::append(polygon, convert(-81.01783333,24.143));
    boost::geometry::append(polygon, convert(-81.02516667,24.13833333));
    boost::geometry::append(polygon, convert(-81.02616667,24.13766667));
    boost::geometry::append(polygon, convert(-81.051,24.12133333));
    boost::geometry::append(polygon, convert(-81.15083333,24.03666667));
    boost::geometry::append(polygon, convert(-81.186,23.99333333));
    boost::geometry::append(polygon, convert(-81.20916667,23.922));
    boost::geometry::append(polygon, convert(-81.32383333,23.892));
    boost::geometry::append(polygon, convert(-81.49316667,23.842));
    boost::geometry::append(polygon, convert(-81.65983333,23.83366667));
    boost::geometry::append(polygon, convert(-81.8265,23.8175));
    boost::geometry::append(polygon, convert(-82.00183333,23.8175));
    boost::geometry::append(polygon, convert(-82.15983333,23.82366667));
    boost::geometry::append(polygon, convert(-82.40983333,23.85233333));
    boost::geometry::append(polygon, convert(-82.65983333,23.85233333));
    boost::geometry::append(polygon, convert(-82.80883333,23.82366667));
    boost::geometry::append(polygon, convert(-82.85183333,23.822));
    boost::geometry::append(polygon, convert(-82.99316667,23.82066667));
    boost::geometry::append(polygon, convert(-83.24316667,23.82533333));
    boost::geometry::append(polygon, convert(-83.42483333,23.85366667));
    boost::geometry::append(polygon, convert(-83.55016667,23.87116667));
    boost::geometry::append(polygon, convert(-83.68916667,23.90066667));
    boost::geometry::append(polygon, convert(-83.80183333,23.9245));
    boost::geometry::append(polygon, convert(-83.99316667,23.973));
    boost::geometry::append(polygon, convert(-84.48783333,24.15616667));
    boost::geometry::append(polygon, convert(-84.63983333,24.22));
    boost::geometry::append(polygon, convert(-84.76783333,24.2735));
    boost::geometry::append(polygon, convert(-84.99316667,24.38833333));
    boost::geometry::append(polygon, convert(-85.10316667,24.4395));
    boost::geometry::append(polygon, convert(-85.52566667,24.64283333));
    boost::geometry::append(polygon, convert(-85.7185,24.73616667));
    boost::geometry::append(polygon, convert(-85.99316667,24.89283333));
    boost::geometry::append(polygon, convert(-86.50116667,25.174));
    boost::geometry::append(polygon, convert(-86.35233333,25.71916667));
    boost::geometry::append(polygon, convert(-86.1075,26.21883333));
    boost::geometry::append(polygon, convert(-86.21916667,26.45366667));
    boost::geometry::append(polygon, convert(-86.61783333,26.55766667));
    boost::geometry::append(polygon, convert(-87.48916667,26.02066667));
    boost::geometry::append(polygon, convert(-88.55,25.70416667));
    boost::geometry::append(polygon, convert(-90.49016667,25.77566667));
    boost::geometry::append(polygon, convert(-90.78416667,25.73983333));
    boost::geometry::append(polygon, convert(-91.875,25.85716667));
    boost::geometry::append(polygon, convert(-93.05983333,26.29066667));
    boost::geometry::append(polygon, convert(-93.55866667,25.9925));
    boost::geometry::append(polygon, convert(-95.6545,26.00533333));
    boost::geometry::append(polygon, convert(-96.805,26.0055));
    boost::geometry::append(polygon, convert(-96.92133333,25.972));
    boost::geometry::append(polygon, convert(-96.9735,25.96916667));
    boost::geometry::append(polygon, convert(-97.02566667,25.95966667));
    boost::geometry::append(polygon, convert(-97.08466667,25.95683333));
    boost::geometry::append(polygon, convert(-97.13683333,25.954));
    boost::geometry::append(polygon, convert(-97.14116667,25.954));
    boost::geometry::append(polygon, convert(-97.81605295593207,27.01607612255437));
    boost::geometry::append(polygon, convert(-91.76985060722265,35.3356681601088));
    boost::geometry::append(polygon, convert(-84.89571294528193,41.0738644453726));
    boost::geometry::append(polygon, convert(-70.34043050675062,54.64100005535186));
    boost::geometry::append(polygon, convert(-64.156,60));
    ASSERT_FALSE(boost::geometry::intersects(convert(-78.1239,25.9556),polygon));
    ASSERT_FALSE(boost::geometry::within(convert(-78.1239,25.9556),polygon));
    ASSERT_FALSE(boost::geometry::within(convert(-78.1239,25.95),polygon));
}
