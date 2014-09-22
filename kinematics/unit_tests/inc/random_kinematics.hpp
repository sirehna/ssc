#ifndef RANDOMKINEMATICS_HPP_
#define RANDOMKINEMATICS_HPP_

#include "Point.hpp"
#include "PointMatrix.hpp"
#include "Transform.hpp"

namespace ssc
{
    namespace random_data_generator
    {
        class DataGenerator;
    }
}

ssc::kinematics::Point random_point_in_frame(const ssc::random_data_generator::DataGenerator& a, const std::string& frame);
ssc::kinematics::Point random_point(const ssc::random_data_generator::DataGenerator& a);
ssc::kinematics::PointMatrix random_point_matrix(const ssc::random_data_generator::DataGenerator& a);
ssc::kinematics::PointMatrix random_point_matrix_in_frame(const ssc::random_data_generator::DataGenerator& a, const std::string& frame);
ssc::kinematics::Transform random_transform(const ssc::random_data_generator::DataGenerator& a, const std::string& from_frame, const std::string& to_frame);

#endif  /* RANDOMKINEMATICS_HPP_ */
