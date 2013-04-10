/*
 * LongitudeLatitudeGenerators.cpp
 *
 * \date 27 mars 2013, 16:22:14
 *  \author cec
 */

#include "LongitudeLatitudeGenerators.hpp"

template <> LongitudeLatitude get_min_bound() {return LongitudeLatitude(-180,-90);}
template <> LongitudeLatitude get_max_bound() {return LongitudeLatitude(180,90);}

template <> LongitudeLatitude TypedScalarDataGenerator<LongitudeLatitude>::get() const
{
    return LongitudeLatitude(random<double>().between(-180,180),random<double>().between(-90,90));
}

