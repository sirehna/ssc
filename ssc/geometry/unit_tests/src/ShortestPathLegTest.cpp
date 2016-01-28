/*
 * LegTest.cpp
 *
 * \date 9 avr. 2013, 14:54:18
 *  \author cec
 */

#include "ShortestPathLegTest.hpp"
#include "ssc/geometry/ShortestPathLeg.hpp"
#include "LatitudeLongitudeGenerators.hpp"
#include "ssc/macros/extra_test_assertions.hpp"
#include <algorithm> // std::min, std::max
#include <cmath>

#define PI 4.*atan(1.)

using namespace ssc::geometry;

ShortestPathLegTest::ShortestPathLegTest() : a(ssc::random_data_generator::DataGenerator(8796))
{
}

ShortestPathLegTest::~ShortestPathLegTest()
{
}

void ShortestPathLegTest::SetUp()
{
}

void ShortestPathLegTest::TearDown()
{
}

TEST_F(ShortestPathLegTest, example)
{
//! [LegTest example]
    // Start by defining the two points composing the leg
    const LatitudeLongitude boston(42.3583,-71.0603),
                            houston(29.7631,-95.3631);
    // Construct the leg
    const ShortestPathLeg leg = ShortestPathLeg::build(boston, houston);
    // We can now compute the length of the leg
    const double distance_between_boston_and_houston = leg.length();
//! [LegTest example]
//! [LegTest expected output]
    ASSERT_DOUBLE_EQ(2583009.0737499665, distance_between_boston_and_houston);
//! [LegTest expected output]
}

TEST_F(ShortestPathLegTest, should_be_able_to_compute_the_distance_between_two_points)
{
//! [LegTest length_example]
    // Define a series of points on the globe
    const LatitudeLongitude boston(42.3583,-71.0603),
                            houston(29.7631,-95.3631),
                            chicago(41.85,-87.65),
                            los_angeles(34.0522,-118.2428);
    // Construct legs between those points
    const ShortestPathLeg boston_houston = ShortestPathLeg::build(boston, houston);
    const ShortestPathLeg houston_chicago = ShortestPathLeg::build(houston, chicago);
    const ShortestPathLeg houston_los_angeles = ShortestPathLeg::build(chicago, los_angeles);
    const ShortestPathLeg boston_los_angeles = ShortestPathLeg::build(boston, los_angeles);
    // The geodesic distances on the WGS84 are then given by the method length()
    ASSERT_NEAR(2583009.0737499665, boston_houston.length(),1E-6);
    ASSERT_NEAR(1509875.9483076334, houston_chicago.length(),1E-6);
    ASSERT_NEAR(2807378.1345177018, houston_los_angeles.length(),1E-6);
    ASSERT_NEAR(4178586.7239053571, boston_los_angeles.length(),1E-6);
//! [LegTest length_example]
}

TEST_F(ShortestPathLegTest, should_throw_if_attempting_to_find_a_point_outside_the_leg)
{
    for (size_t i = 0 ; i < 200 ; ++i)
    {
        //! [LegTest find_waypoint_at_example]
        // Definie the two waypoints composing the leg
        const LatitudeLongitude point1 = a.random<LatitudeLongitude>();
        const LatitudeLongitude point2 = a.random<LatitudeLongitude>();
        // Construct the leg
        const ShortestPathLeg leg = ShortestPathLeg::build(point1, point2);
        // The input argument must be between 0 and the leg length, otherwise an exception is thrown
        ASSERT_THROW(leg.find_waypoint_at(a.random<double>().no().greater_than(0)), LegException);
        ASSERT_THROW(leg.find_waypoint_at(a.random<double>().greater_than(leg.length())), LegException);
        //! [LegTest find_waypoint_at_example]
    }
}

TEST_F(ShortestPathLegTest, should_be_able_to_find_a_waypoint_on_a_leg_on_a_meridian)
{
    for (size_t i = 0 ; i < 200 ; ++i)
    {
        const double latitude1 = a.random<double>().between(-90,90);
        const double latitude2 = a.random<double>().between(-90,90);
        const double longitude = a.random<double>().between(-180,180);
        const LatitudeLongitude point1(latitude1,longitude);
        const LatitudeLongitude point2(latitude2,longitude);
        const ShortestPathLeg leg = ShortestPathLeg::build(point1, point2);
        const double L = leg.length();
        for (size_t j = 0 ; j < 10 ; ++j)
        {
            const double d = a.random<double>().between(0, L);
            const LatitudeLongitude intermediate = leg.find_waypoint_at(d);
            ASSERT_DOUBLE_EQ(longitude, intermediate.lon);
        }
    }
}

TEST_F(ShortestPathLegTest, should_be_able_to_find_a_waypoint_on_the_equator)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double longitude1 = a.random<double>().between(-180,180);
        const double delta_longitude = a.random<double>().between(-130,130);
        const double longitude2 = std::max(-180.,std::min(longitude1+delta_longitude,180.));
        const double latitude = 0;//a.random<double>().between(-90,90);
        const LatitudeLongitude point1(latitude,longitude1);
        const LatitudeLongitude point2(latitude,longitude2);
        const ShortestPathLeg leg = ShortestPathLeg::build(point1, point2);
        const double L = leg.length();
        for (size_t j = 0 ; j < 10 ; ++j)
        {
            const double d = a.random<double>().between(0, L);
            const LatitudeLongitude intermediate = leg.find_waypoint_at(d);
            ASSERT_DOUBLE_EQ(latitude, intermediate.lat);
        }
    }
}

TEST_F(ShortestPathLegTest, distance_from_start_to_intermediate_waypoint_should_always_be_less_than_leg_length)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const LatitudeLongitude point1 = a.random<LatitudeLongitude>();
        const LatitudeLongitude point2 = a.random<LatitudeLongitude>();
        const ShortestPathLeg leg = ShortestPathLeg::build(point1, point2);
        const double leg_length = leg.length();
        const double d = a.random<double>().between(0, leg_length);
        const LatitudeLongitude intermediate = leg.find_waypoint_at(d);
        ASSERT_LE(ShortestPathLeg::build(point1, intermediate).length(), leg_length);
    }
}

TEST_F(ShortestPathLegTest, distance_from_start_to_intermediate_waypoint_should_correspond_to_the_input)
{
    const double eps = 1e-10;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const LatitudeLongitude point1 = a.random<LatitudeLongitude>();
        const LatitudeLongitude point2 = a.random<LatitudeLongitude>();
        const ShortestPathLeg leg = ShortestPathLeg::build(point1, point2);
        const double leg_length = leg.length();
        const double d = a.random<double>().between(0, leg_length);
        const LatitudeLongitude intermediate = leg.find_waypoint_at(d);
        ASSERT_SMALL_RELATIVE_ERROR(ShortestPathLeg::build(point1, intermediate).length(), d, eps);
    }
}

TEST_F(ShortestPathLegTest, distance_between_miami_and_WP1_on_Norwegian_Epic_cruise_should_be_calculated_properly)
{
    const LatitudeLongitude miami(25.7744,80.1637);
    const LatitudeLongitude wpA(26.1802,79.099);
    ASSERT_NEAR(115.706, ShortestPathLeg::build(miami,wpA).length()/1e3, 1e-3);
}


TEST_F(ShortestPathLegTest, can_calculate_heading_on_leg_on_equator_for_any_point_on_leg)
{
    //! [LegTest azimuth_at_example]
    const LatitudeLongitude P(0, a.random<double>().between(-180,180));
    const LatitudeLongitude Q(0, a.random<double>().between(-180,180));
    const ShortestPathLeg l = ShortestPathLeg::build(P,Q);
    const double d = l.length();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        ASSERT_DOUBLE_EQ(90, fabs(l.azimuth_at(a.random<double>().between(0, d)).get_degree()));
    }
    //! [LegTest azimuth_at_example]
}

TEST_F(ShortestPathLegTest, bug_detected_in_NorwegianEpicDataPreProcessorTest)
{
    const ShortestPathLeg leg = ShortestPathLeg::build(LatitudeLongitude(0,0),LatitudeLongitude(0,1));
    ASSERT_DOUBLE_EQ(90, leg.azimuth_at(0).get_degree());
}

TEST_F(ShortestPathLegTest, can_calculate_heading_on_leg_on_meridian_for_any_point_on_leg)
{
    const LatitudeLongitude P(a.random<double>().between(-90,90), 0);
    const LatitudeLongitude Q(a.random<double>().between(-90,90), 0);
    const ShortestPathLeg l = ShortestPathLeg::build(P,Q);
    const double d = l.length();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        ASSERT_DOUBLE_EQ(0, fmod(l.azimuth_at(a.random<double>().between(0, d)).get_radian(),PI));
    }
}

TEST_F(ShortestPathLegTest, bug_detected_in_EONAV)
{
    const LatitudeLongitude A(48.049, -5.39569);
    const LatitudeLongitude B(47.9594, -5.55477);
    const LatitudeLongitude P(48.1213, -5.18037);
    const ShortestPathLeg l = ShortestPathLeg::build(A,B);
    const LatitudeLongitude Q = l.find_closest_point_to(P);
    ASSERT_LE(Q.lat, std::max(A.lat, B.lat));
    ASSERT_GE(Q.lat, std::min(A.lat, B.lat));
    ASSERT_LE(Q.lon, std::max(A.lon, B.lon));
    ASSERT_GE(Q.lon, std::min(A.lon, B.lon));
}
