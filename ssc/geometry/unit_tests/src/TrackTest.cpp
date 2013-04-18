/*
 * TrackTest.cpp
 *
 * \date 8 avr. 2013, 15:15:05
 *  \author cec
 */

#include "TrackTest.hpp"
#include "Track.hpp"
#include "LongitudeLatitudeGenerators.hpp"
#include "extra_test_assertions.hpp"
#include "test_macros.hpp"

TrackTest::TrackTest() : a(DataGenerator(557))
{
}

TrackTest::~TrackTest()
{
}

void TrackTest::SetUp()
{
}

void TrackTest::TearDown()
{
}

TEST_F(TrackTest, example)
{
//! [TrackTest example]
    // Start by declaring the waypoints (at least two)
    LongitudeLatitude boston(-71.0603,42.3583),
                      houston(-95.3631,29.7631),
                      chicago(-87.65,41.85),
                      los_angeles(-118.2428,34.0522);
    // Specify the departure & arrival dates, making sure arrival is after departure)
    const Date departure = a.random<double>().greater_than(0);
    const Date arrival = a.random<double>().greater_than((double)departure);
    // Declare track
    Track track({boston, houston, chicago, los_angeles}, departure, arrival);
//! [TrackTest example]
//! [TrackTest expected output]
    // Calculate track length
    ASSERT_DOUBLE_EQ(6900263.1565753017, track.length());
//! [TrackTest expected output]
}

TEST_F(TrackTest, should_throw_if_track_has_fewer_than_two_points)
{
    const std::vector<LongitudeLatitude> empty;
    const std::vector<LongitudeLatitude> only_one_longitude_latitude(1,a.random<LongitudeLatitude>());
    const Date departure = a.random<double>().greater_than(0);
    const Date arrival = a.random<double>().greater_than((double)departure);
    ASSERT_THROW(Track(empty, departure, arrival), TrackException);
    ASSERT_THROW(Track(only_one_longitude_latitude, departure, arrival), TrackException);
    for (size_t i = 2 ; i < 100 ; ++i)
    {
        const std::vector<LongitudeLatitude> waypoints(i,a.random<LongitudeLatitude>());
        ASSERT_NO_THROW(Track(waypoints, departure, arrival));
    }
}

TEST_F(TrackTest,should_throw_if_departure_date_is_later_than_arrival_date)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,10);
        const std::vector<LongitudeLatitude> waypoints = a.random_vector_of<LongitudeLatitude>().of_size(n);
        const Date arrival = a.random<double>().greater_than(0);
        const Date departure_later_than_arrival = a.random<double>().greater_than((double)arrival);
        ASSERT_THROW(Track(waypoints, departure_later_than_arrival, arrival), TrackException);
        ASSERT_NO_THROW(Track(waypoints, arrival, arrival));
    }
}

TEST_F(TrackTest,should_throw_if_any_date_is_negative)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const std::vector<LongitudeLatitude> waypoints = a.random_vector_of<LongitudeLatitude>().of_size(3);
        const Date departure = a.random<double>().greater_than(0);
        const Date arrival = a.random<double>().greater_than((double)departure);
        const Date negative_departure = a.random<double>().no().greater_than(0);
        const Date negative_arrival = a.random<double>().between((double)departure,0);
        ASSERT_THROW(Track(waypoints, negative_departure, arrival), TrackException);
        ASSERT_THROW(Track(waypoints, departure, negative_arrival), TrackException);
        ASSERT_THROW(Track(waypoints, negative_departure, negative_arrival), TrackException);
    }
}

TEST_F(TrackTest, should_be_able_to_compute_distance_from_start_of_track_of_a_given_waypoint)
{
    //! [TrackTest distance_from_start_example]
    // Define a series of points on the globe
    LongitudeLatitude boston(-71.0603,42.3583),
                      houston(-95.3631,29.7631),
                      chicago(-87.65,41.85),
                      los_angeles(-118.2428,34.0522);
    // Any departure & arrival date will do for this example
    const Date departure = a.random<double>().greater_than(0);
    const Date arrival = a.random<double>().greater_than((double)departure);
    // Construct the track
    const Track track({boston, houston, chicago, los_angeles}, departure, arrival);
    // The distances of each waypoint from the start of the leg are then given by distance_from_start
    ASSERT_DOUBLE_EQ(0, track.get_waypoint_position_on_track(0));
    ASSERT_DOUBLE_EQ(2583009.0737499665, track.get_waypoint_position_on_track(1));
    ASSERT_DOUBLE_EQ(1509875.9483076334+track.get_waypoint_position_on_track(1), track.get_waypoint_position_on_track(2));
    ASSERT_DOUBLE_EQ(2807378.1345177018+track.get_waypoint_position_on_track(2), track.get_waypoint_position_on_track(3));
    //! [TrackTest distance_from_start_example]
}

TEST_F(TrackTest, should_be_able_to_find_leg_index_from_distance_on_track)
{
    const double eps=1e-5;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const size_t nb_of_waypoints = a.random<size_t>().between(2, 10);
        const std::vector<LongitudeLatitude> waypoints = a.random_vector_of<LongitudeLatitude>().of_size(nb_of_waypoints);
        const Date departure = a.random<double>().greater_than(0);
        const Date arrival = a.random<double>().greater_than((double)departure);
        const Track track(waypoints, departure, arrival);
        const size_t leg_index = a.random<size_t>().between(0,nb_of_waypoints-2);
        const double position_of_first_point = track.get_waypoint_position_on_track(leg_index);
        const double position_of_second_point = track.get_waypoint_position_on_track(leg_index+1);
        ASSERT_EQ(leg_index, track.find_leg_index(position_of_first_point+eps));
        if (leg_index == nb_of_waypoints-2)
        {
            ASSERT_EQ(leg_index, track.find_leg_index(position_of_second_point+eps));
        }
        else
        {
            ASSERT_EQ(leg_index+1, track.find_leg_index(position_of_second_point+eps));
        }
        for (size_t j = 0 ; j< 10 ; ++j)
        {
            const double d = a.random<double>().between(position_of_first_point,position_of_second_point).but_not(position_of_second_point);
            ASSERT_EQ(leg_index, track.find_leg_index(d));
        }
    }
}

TEST_F(TrackTest, leg_index_example)
{
    //! [TrackTest find_leg_index_example]
    // Define a series of points on the globe
    LongitudeLatitude boston(-71.0603,42.3583),
                      houston(-95.3631,29.7631),
                      chicago(-87.65,41.85),
                      los_angeles(-118.2428,34.0522);
    // Any departure & arrival date will do for this example
    const Date departure = a.random<double>().greater_than(0);
    const Date arrival = a.random<double>().greater_than((double)departure);
    // Construct the track
    const Track track({boston, houston, chicago, los_angeles}, departure, arrival);
    // For any point between waypoints 2 & 3, the returned index should be 1 because they are on the second leg (indexes start at 0)
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        ASSERT_EQ(1, track.find_leg_index(a.random<double>().between(track.get_waypoint_position_on_track(1),track.get_waypoint_position_on_track(2))));
    }
    //! [TrackTest find_leg_index_example]
}

TEST_F(TrackTest, should_be_able_to_find_a_waypoint_on_track)
{
    //! [TrackTest find_waypoint_on_track_example]
    // Define a series of points on the globe
    LongitudeLatitude boston(-71.0603,42.3583),
                      houston(-95.3631,29.7631),
                      chicago(-87.65,41.85),
                      los_angeles(-118.2428,34.0522);
    // Any departure & arrival date will do for this example
    const Date departure = a.random<double>().greater_than(0);
    const Date arrival = a.random<double>().greater_than((double)departure);
    // Construct the track
    Track track({boston, houston, chicago, los_angeles}, departure, arrival);

    // In this particular case, we are attempting to find the second point on the track (special case)
    const double eps = 1e-6;
    const LongitudeLatitude p0 = track.find_waypoint_on_track(0);
    ASSERT_SMALL_RELATIVE_ERROR(boston.lat, p0.lat, eps);
    ASSERT_SMALL_RELATIVE_ERROR(boston.lon, p0.lon, eps);
    //! [TrackTest find_waypoint_on_track_example]
    const LongitudeLatitude p1 = track.find_waypoint_on_track(2583009.0737499665-eps);
    ASSERT_SMALL_RELATIVE_ERROR(houston.lat, p1.lat, eps);
    ASSERT_SMALL_RELATIVE_ERROR(houston.lon, p1.lon, eps);

    const LongitudeLatitude p2 = track.find_waypoint_on_track(2583009.0737499665+1509875.9483076334-eps);
    ASSERT_SMALL_RELATIVE_ERROR(chicago.lat, p2.lat, eps);
    ASSERT_SMALL_RELATIVE_ERROR(chicago.lon, p2.lon, eps);

    const LongitudeLatitude p3 = track.find_waypoint_on_track(2583009.0737499665+1509875.9483076334+2807378.1345177018-eps);
    ASSERT_SMALL_RELATIVE_ERROR(los_angeles.lat, p3.lat, eps);
    ASSERT_SMALL_RELATIVE_ERROR(los_angeles.lon, p3.lon, eps);
}
