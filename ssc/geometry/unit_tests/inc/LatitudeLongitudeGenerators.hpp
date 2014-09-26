/*
 * LongitudeLatitudeGenerators.hpp
 *
 * \date 27 mars 2013, 16:21:32
 *  \author cec
 */

#ifndef LONGITUDELATITUDEGENERATORS_HPP_
#define LONGITUDELATITUDEGENERATORS_HPP_

#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/geometry/LatitudeLongitude.hpp"

namespace ssc
{
    namespace random_data_generator
    {
        template <> ssc::geometry::LatitudeLongitude get_min_bound();
        template <> ssc::geometry::LatitudeLongitude get_max_bound();
        template <> ssc::geometry::LatitudeLongitude TypedScalarDataGenerator<ssc::geometry::LatitudeLongitude>::get() const;
    }
}

#endif /* LONGITUDELATITUDEGENERATORS_HPP_ */
