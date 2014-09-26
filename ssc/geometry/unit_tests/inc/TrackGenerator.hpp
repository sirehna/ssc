/*
 * TrackGenerator.hpp
 *
 * \date 11 avr. 2013, 12:41:36
 *  \author cec
 */

#ifndef TRACKGENERATOR_HPP_
#define TRACKGENERATOR_HPP_

#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/geometry/Track.hpp"

namespace ssc
{
    namespace random_data_generator
    {
        template <> ssc::geometry::Track get_min_bound();
        template <> ssc::geometry::Track get_max_bound();
        template <> ssc::geometry::Track TypedScalarDataGenerator<ssc::geometry::Track>::get() const;
    }
}

#endif /* TRACKGENERATOR_HPP_ */
