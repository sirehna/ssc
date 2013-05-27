/*
 * LongitudeLatitudeGenerators.hpp
 *
 * \date 27 mars 2013, 16:21:32
 *  \author cec
 */

#ifndef LONGITUDELATITUDEGENERATORS_HPP_
#define LONGITUDELATITUDEGENERATORS_HPP_

#include "DataGenerator.hpp"
#include "LatitudeLongitude.hpp"

template <> LatitudeLongitude get_min_bound();
template <> LatitudeLongitude get_max_bound();

template <> LatitudeLongitude TypedScalarDataGenerator<LatitudeLongitude>::get() const;



#endif /* LONGITUDELATITUDEGENERATORS_HPP_ */
