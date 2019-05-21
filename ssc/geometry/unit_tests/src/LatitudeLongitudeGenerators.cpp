/*
 * LongitudeLatitudeGenerators.cpp
 *
 * \date 27 mars 2013, 16:22:14
 * \author cec
 */

#include "LatitudeLongitudeGenerators.hpp"

template <> ssc::geometry::LatitudeLongitude ssc::random_data_generator::get_min_bound() {return ssc::geometry::LatitudeLongitude(-90,-180);}
template <> ssc::geometry::LatitudeLongitude ssc::random_data_generator::get_max_bound() {return ssc::geometry::LatitudeLongitude(90,180);}

template <> ssc::geometry::LatitudeLongitude ssc::random_data_generator::TypedScalarDataGenerator<ssc::geometry::LatitudeLongitude>::get() const
{
    return ssc::geometry::LatitudeLongitude(random<double>().between(-90,90),random<double>().between(-180,180));
}

