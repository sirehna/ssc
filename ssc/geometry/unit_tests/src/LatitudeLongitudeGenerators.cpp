/*
 * LongitudeLatitudeGenerators.cpp
 *
 * \date 27 mars 2013, 16:22:14
 *  \author cec
 */

#include "LatitudeLongitudeGenerators.hpp"

template <> LatitudeLongitude ssc::random_data_generator::get_min_bound() {return LatitudeLongitude(-90,-180);}
template <> LatitudeLongitude ssc::random_data_generator::get_max_bound() {return LatitudeLongitude(90,180);}

template <> LatitudeLongitude ssc::random_data_generator::TypedScalarDataGenerator<LatitudeLongitude>::get() const
{
    return LatitudeLongitude(random<double>().between(-90,90),random<double>().between(-180,180));
}

