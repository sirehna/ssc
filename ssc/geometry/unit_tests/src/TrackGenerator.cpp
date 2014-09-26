#include "TrackGenerator.hpp"
#include "LatitudeLongitudeGenerators.hpp"
#include "ShortestPathLegChain.hpp"
#include <algorithm> // std::min, std::max

template <> ssc::geometry::Track ssc::random_data_generator::get_min_bound() {return ssc::geometry::Track({ssc::geometry::LatitudeLongitude(0,0),ssc::geometry::LatitudeLongitude(90,90)}, new ssc::geometry::ShortestPathLegChain());}
template <> ssc::geometry::Track ssc::random_data_generator::get_max_bound() {return ssc::geometry::Track({ssc::geometry::LatitudeLongitude(0,0),ssc::geometry::LatitudeLongitude(90,90)}, new ssc::geometry::ShortestPathLegChain());}

template <> ssc::geometry::Track ssc::random_data_generator::TypedScalarDataGenerator<ssc::geometry::Track>::get() const
{
    const size_t n = random<size_t>().between(2,10);
    return ssc::geometry::Track(random_vector_of<ssc::geometry::LatitudeLongitude>().of_size(n), new ssc::geometry::ShortestPathLegChain());
}


namespace ssc
{
    namespace random_data_generator
    {
        template <> ssc::geometry::Angle TypedScalarDataGenerator<ssc::geometry::Angle>::get() const
        {
            return ssc::geometry::Angle::degree(random<double>().between(0,360));
        }
    }
}

