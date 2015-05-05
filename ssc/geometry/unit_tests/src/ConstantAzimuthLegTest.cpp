/*
 * ConstantAzimuthLegTest.cpp
 *
 *  Created on: May 14, 2014
 *      Author: cady
 */

#include <algorithm> // std::mi std::max

#include "ConstantAzimuthLegTest.hpp"
#include "ssc/geometry/ConstantAzimuthLeg.hpp"
#include "LatitudeLongitudeGenerators.hpp"

#define EPS 1E-6

using namespace ssc::geometry;

ConstantAzimuthLegTest::ConstantAzimuthLegTest() : a(ssc::random_data_generator::DataGenerator(121))
{
}

ConstantAzimuthLegTest::~ConstantAzimuthLegTest()
{
}

void ConstantAzimuthLegTest::SetUp()
{
}

void ConstantAzimuthLegTest::TearDown()
{
}

TEST_F(ConstantAzimuthLegTest, example)
{
//! [ConstantAzimuthLegTest example]
    // Start by defining the two points composing the leg
    const LatitudeLongitude Murray_Spring(-(36  + 47/60. + 49.2232/3600),(148 + 11/60. + 48.3333/3600)),
                            Wauka_1978(-(37  + 30/60. + 18.0674/3600),(149  + 58/60. + 32.9932/3600));
    // Construct the leg
    const ConstantAzimuthLeg leg = ConstantAzimuthLeg::build(Murray_Spring, Wauka_1978);
    // We can now compute the length of the leg
    const double distance_between_Murray_Spring_and_Wauka_1978 = leg.length();
//! [ConstantAzimuthLegTest example]
//! [ConstantAzimuthLegTest expected output]
    ASSERT_NEAR(176497.82995137692, distance_between_Murray_Spring_and_Wauka_1978, EPS);

    const LatitudeLongitude P = leg.find_waypoint_at(176497.82995137692);
    ASSERT_NEAR(Wauka_1978.lat, P.lat, EPS);
    ASSERT_NEAR(Wauka_1978.lon, P.lon, EPS);
//! [ConstantAzimuthLegTest expected output]
}

TEST_F(ConstantAzimuthLegTest, should_be_able_to_find_a_waypoint_on_a_leg_on_a_meridian)
{
    for (size_t i = 0 ; i < 200 ; ++i)
    {
        const double latitude1 = a.random<double>().between(-90,90);
        const double latitude2 = a.random<double>().between(-90,90);
        const double longitude = a.random<double>().between(-180,180);
        const LatitudeLongitude point1(latitude1,longitude);
        const LatitudeLongitude point2(latitude2,longitude);
        const ConstantAzimuthLeg leg = ConstantAzimuthLeg::build(point1, point2);
        const double L = leg.length();
        for (size_t j = 0 ; j < 10 ; ++j)
        {
            const double d = a.random<double>().between(0, L);
            const LatitudeLongitude intermediate = leg.find_waypoint_at(d);
            ASSERT_NEAR(longitude, intermediate.lon, EPS);
        }
    }
}

TEST_F(ConstantAzimuthLegTest, can_compute_distance_of_two_points_on_equator)
{
    const LatitudeLongitude A(LatitudeLongitude(0,1));
    const LatitudeLongitude B(LatitudeLongitude(0,2));
    ASSERT_LT(0,distance<ConstantAzimuthLeg>(A,B));
}

TEST_F(ConstantAzimuthLegTest, should_be_able_to_find_closest_waypoint_on_equator)
{
    for (size_t i = 0 ; i < 50 ; ++i)
    {
        LatitudeLongitude A(a.random<LatitudeLongitude>());A.lat = 0;
        LatitudeLongitude B(a.random<LatitudeLongitude>());B.lat = 0;
        LatitudeLongitude M(a.random<LatitudeLongitude>());
        M.lon = a.random<double>().between(std::min(A.lon,B.lon), std::max(A.lon,B.lon));

        const ConstantAzimuthLeg leg = ConstantAzimuthLeg::build(A, B);
        const LatitudeLongitude P = leg.find_closest_point_to(M);
        ASSERT_GT(distance<ConstantAzimuthLeg>(P,M),EPS);
        ASSERT_NEAR(0, P.lat, EPS);
    }
}

TEST_F(ConstantAzimuthLegTest, should_be_able_to_find_closest_waypoint_on_meridian)
{
    const double lon = a.random<double>().between(-100,100);
    LatitudeLongitude A(a.random<LatitudeLongitude>());A.lon = lon;
    LatitudeLongitude B(a.random<LatitudeLongitude>());B.lon = lon;
    LatitudeLongitude M(a.random<double>().between(std::min(A.lat,B.lat), std::max(A.lat,B.lat)),a.random<double>().between(lon-50,lon+50));

    const ConstantAzimuthLeg leg = ConstantAzimuthLeg::build(A, B);
    const LatitudeLongitude P = leg.find_closest_point_to(M);

    ASSERT_GT(distance<ConstantAzimuthLeg>(P,M),EPS);
    ASSERT_NEAR(lon, P.lon, EPS);

    ASSERT_LT(std::min(A.lat,B.lat), P.lat+1E-10);
    ASSERT_LT(P.lat, std::max(A.lat,B.lat)+1E-10);
}

TEST_F(ConstantAzimuthLegTest, should_be_able_to_find_closest_waypoint_on_any_parallel)
{
    LatitudeLongitude A(a.random<LatitudeLongitude>());
    LatitudeLongitude B(a.random<LatitudeLongitude>());B.lat = A.lat;
    LatitudeLongitude M(a.random<LatitudeLongitude>());
    M.lon = a.random<double>().between(std::min(A.lon,B.lon), std::max(A.lon,B.lon));

    const ConstantAzimuthLeg leg = ConstantAzimuthLeg::build(A, B);
    const LatitudeLongitude P = leg.find_closest_point_to(M);

    ASSERT_GT(distance<ConstantAzimuthLeg>(P,M),EPS);
    ASSERT_NEAR(A.lat, P.lat, EPS);
}
