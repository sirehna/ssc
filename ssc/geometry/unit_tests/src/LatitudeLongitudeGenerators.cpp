/*
 * LongitudeLatitudeGenerators.cpp
 *
 * \date 27 mars 2013, 16:22:14
 *  \author cec
 */

#include "LatitudeLongitudeGenerators.hpp"

template <> LatitudeLongitude get_min_bound() {return LatitudeLongitude(-90,-180);}
template <> LatitudeLongitude get_max_bound() {return LatitudeLongitude(90,180);}

template <> LatitudeLongitude TypedScalarDataGenerator<LatitudeLongitude>::get() const
{
    return LatitudeLongitude(random<double>().between(-90,90),random<double>().between(-180,180));
}

