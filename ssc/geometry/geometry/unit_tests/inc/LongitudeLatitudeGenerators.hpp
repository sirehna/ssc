/*
 * LongitudeLatitudeGenerators.hpp
 *
 * \date 27 mars 2013, 16:21:32
 *  \author cec
 */

#ifndef LONGITUDELATITUDEGENERATORS_HPP_
#define LONGITUDELATITUDEGENERATORS_HPP_

#include "DataGenerator.hpp"
#include "LongitudeLatitude.hpp"

template <> LongitudeLatitude get_min_bound();
template <> LongitudeLatitude get_max_bound();

template <> LongitudeLatitude TypedScalarDataGenerator<LongitudeLatitude>::get() const;



#endif /* LONGITUDELATITUDEGENERATORS_HPP_ */
