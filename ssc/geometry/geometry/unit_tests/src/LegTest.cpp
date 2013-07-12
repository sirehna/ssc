/*
 * LegTest.cpp
 *
 * \date 9 avr. 2013, 14:54:18
 *  \author cec
 */

#include "LegTest.hpp"
#include "Leg.hpp"
#include "LatitudeLongitudeGenerators.hpp"
#include "extra_test_assertions.hpp"
#include <algorithm> // std::min, std::max
#include <cmath>

#define PI 4.*atan(1.)

LegTest::LegTest() : a(DataGenerator(8796))
{
}

LegTest::~LegTest()
{
}

void LegTest::SetUp()
{
}

void LegTest::TearDown()
{
}

TEST_F(LegTest, example)
{
//! [LegTest example]
    // Start by defining the two points composing the leg
    const LatitudeLongitude boston(42.3583,-71.0603),
                            houston(29.7631,-95.3631);
    // Construct the leg
    const Leg leg(boston, houston);
    // We can now compute the length of the leg
    const double distance_between_boston_and_houston = leg.length();
//! [LegTest example]
//! [LegTest expected output]
    ASSERT_DOUBLE_EQ(2583009.0737499665, distance_between_boston_and_houston);
//! [LegTest expected output]
}

TEST_F(LegTest, should_be_able_to_compute_the_distance_between_two_points)
{
//! [LegTest length_example]
    // Define a series of points on the globe
    const LatitudeLongitude boston(42.3583,-71.0603),
                            houston(29.7631,-95.3631),
                            chicago(41.85,-87.65),
                            los_angeles(34.0522,-118.2428);
    // Construct legs between those points
    const Leg boston_houston(boston, houston);
    const Leg houston_chicago(houston, chicago);
    const Leg houston_los_angeles(chicago, los_angeles);
    const Leg boston_los_angeles(boston, los_angeles);
    // The geodesic distances on the WGS84 are then given by the method length()
    ASSERT_DOUBLE_EQ(2583009.0737499665, boston_houston.length());
    ASSERT_DOUBLE_EQ(1509875.9483076334, houston_chicago.length());
    ASSERT_DOUBLE_EQ(2807378.1345177018, houston_los_angeles.length());
    ASSERT_DOUBLE_EQ(4178586.7239053571, boston_los_angeles.length());
//! [LegTest length_example]
}

TEST_F(LegTest, should_throw_if_attempting_to_find_a_point_outside_the_leg)
{
    for (size_t i = 0 ; i < 200 ; ++i)
    {
        //! [LegTest find_waypoint_at_example]
        // Definie the two waypoints composing the leg
        const LatitudeLongitude point1 = a.random<LatitudeLongitude>();
        const LatitudeLongitude point2 = a.random<LatitudeLongitude>();
        // Construct the leg
        const Leg leg(point1, point2);
        // The input argument must be between 0 and the leg length, otherwise an exception is thrown
        ASSERT_THROW(leg.find_waypoint_at(a.random<double>().no().greater_than(0)), LegException);
        ASSERT_THROW(leg.find_waypoint_at(a.random<double>().greater_than(leg.length())), LegException);
        //! [LegTest find_waypoint_at_example]
    }
}

TEST_F(LegTest, should_be_able_to_find_a_waypoint_on_a_leg_on_a_meridian)
{
    for (size_t i = 0 ; i < 200 ; ++i)
    {
        const double latitude1 = a.random<double>().between(-90,90);
        const double latitude2 = a.random<double>().between(-90,90);
        const double longitude = a.random<double>().between(-180,180);
        const LatitudeLongitude point1(latitude1,longitude);
        const LatitudeLongitude point2(latitude2,longitude);
        const Leg leg(point1, point2);
        const double L = leg.length();
        for (size_t j = 0 ; j < 10 ; ++j)
        {
            const double d = a.random<double>().between(0, L);
            const LatitudeLongitude intermediate = leg.find_waypoint_at(d);
            ASSERT_DOUBLE_EQ(longitude, intermediate.lon);
        }
    }
}

TEST_F(LegTest, should_be_able_to_find_a_waypoint_on_the_equator)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double longitude1 = a.random<double>().between(-180,180);
        const double delta_longitude = a.random<double>().between(-130,130);
        const double longitude2 = std::max(-180.,std::min(longitude1+delta_longitude,180.));
        const double latitude = 0;//a.random<double>().between(-90,90);
        const LatitudeLongitude point1(latitude,longitude1);
        const LatitudeLongitude point2(latitude,longitude2);
        const Leg leg(point1, point2);
        const double L = leg.length();
        for (size_t j = 0 ; j < 10 ; ++j)
        {
            const double d = a.random<double>().between(0, L);
            const LatitudeLongitude intermediate = leg.find_waypoint_at(d);
            ASSERT_DOUBLE_EQ(latitude, intermediate.lat);
        }
    }
}

TEST_F(LegTest, distance_from_start_to_intermediate_waypoint_should_always_be_less_than_leg_length)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const LatitudeLongitude point1 = a.random<LatitudeLongitude>();
        const LatitudeLongitude point2 = a.random<LatitudeLongitude>();
        const Leg leg(point1, point2);
        const double leg_length = leg.length();
        const double d = a.random<double>().between(0, leg_length);
        const LatitudeLongitude intermediate = leg.find_waypoint_at(d);
        ASSERT_LE(Leg(point1, intermediate).length(), leg_length);
    }
}

TEST_F(LegTest, distance_from_start_to_intermediate_waypoint_should_correspond_to_the_input)
{
    const double eps = 1e-10;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const LatitudeLongitude point1 = a.random<LatitudeLongitude>();
        const LatitudeLongitude point2 = a.random<LatitudeLongitude>();
        const Leg leg(point1, point2);
        const double leg_length = leg.length();
        const double d = a.random<double>().between(0, leg_length);
        const LatitudeLongitude intermediate = leg.find_waypoint_at(d);
        ASSERT_SMALL_RELATIVE_ERROR(Leg(point1, intermediate).length(), d, eps);
    }
}

TEST_F(LegTest, distance_between_miami_and_WP1_on_Norwegian_Epic_cruise_should_be_calculated_properly)
{
    const LatitudeLongitude miami(25.7744,80.1637);
    const LatitudeLongitude wpA(26.1802,79.099);
    ASSERT_NEAR(115.706, Leg(miami,wpA).length()/1e3, 1e-3);
}


TEST_F(LegTest, can_calculate_heading_on_leg_on_equator_for_any_point_on_leg)
{
    //! [LegTest azimuth_at_example]
    const LatitudeLongitude P(0, a.random<double>().between(-180,180));
    const LatitudeLongitude Q(0, a.random<double>().between(-180,180));
    const Leg l(P,Q);
    const double d = l.length();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        ASSERT_DOUBLE_EQ(90, fabs(l.azimuth_at(a.random<double>().between(0, d)).get_degree()));
    }
    //! [LegTest azimuth_at_example]
}

TEST_F(LegTest, can_calculate_heading_on_leg_on_meridian_for_any_point_on_leg)
{
    const LatitudeLongitude P(a.random<double>().between(-90,90), 0);
    const LatitudeLongitude Q(a.random<double>().between(-90,90), 0);
    const Leg l(P,Q);
    const double d = l.length();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        ASSERT_DOUBLE_EQ(0, fmod(l.azimuth_at(a.random<double>().between(0, d)).get_radian(),PI));
    }
}
