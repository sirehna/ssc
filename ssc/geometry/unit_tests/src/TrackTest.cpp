/*
 * TrackTest.cpp
 *
 * \date 8 avr. 2013, 15:15:05
 *  \author cec
 */

#include "TrackTest.hpp"
#include "Track.hpp"
#include "LongitudeLatitudeGenerators.hpp"

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
    ASSERT_DOUBLE_EQ(6900263.1565753017, track.distance());
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
    for (size_t i = 2 ; i < 1000 ; ++i)
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

TEST_F(TrackTest, should_be_able_to_compute_the_distance_between_two_points)
{
    LongitudeLatitude boston(-71.0603,42.3583),
                      houston(-95.3631,29.7631),
                      chicago(-87.65,41.85),
                      los_angeles(-118.2428,34.0522);
    const Date departure = a.random<double>().greater_than(0);
    const Date arrival = a.random<double>().greater_than((double)departure);
    const Track boston_houston({boston, houston}, departure, arrival);
    const Track houston_chicago({houston, chicago}, departure, arrival);
    const Track houston_los_angeles({chicago, los_angeles}, departure, arrival);
    const Track boston_los_angeles({boston, los_angeles}, departure, arrival);
    ASSERT_DOUBLE_EQ(2583009.0737499665, boston_houston.distance());
    ASSERT_DOUBLE_EQ(1509875.9483076334, houston_chicago.distance());
    ASSERT_DOUBLE_EQ(2807378.1345177018, houston_los_angeles.distance());
    ASSERT_DOUBLE_EQ(4178586.7239053571, boston_los_angeles.distance());
}
