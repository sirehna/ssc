/*
 * Transform.hpp
 *
 *  Created on: 8 avr. 2014
 *      Author: cec
 */

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include <ostream>

#include "ssc/kinematics/Point.hpp"
#include "ssc/kinematics/PointMatrix.hpp"
#include "ssc/kinematics/RotationMatrix.hpp"
#include "ssc/kinematics/Velocity.hpp"

namespace ssc
{
    namespace kinematics
    {
        /** \author cec
         *  \brief Can express positions, speeds & wrenches in a different frame of reference.
         *  \details
         *  \ingroup kinematics
         *  \section ex1 Example
         *  \snippet kinematics/unit_tests/src/TransformTest.cpp TransformTest example
         *  \section ex2 Expected output
         *  \snippet kinematics/unit_tests/src/TransformTest.cpp TransformTest expected output
         */
        class Transform
        {
            public:
                Transform();
                Transform(const Point& translation, const RotationMatrix& rotation, const std::string& to_frame);
                Transform(const Point& translation, const std::string& to_frame);
                Transform(const RotationMatrix& rotation, const std::string& from_frame, const std::string& to_frame);
                Eigen::Vector3d operator*(const Eigen::Vector3d& P) const;
                Point operator*(const Point& P) const;
                PointMatrix operator*(const PointMatrix& P) const;
                PointMatrix operator*(const PointMatrixPtr& P) const;
                Velocity operator*(const Velocity& P) const;
                Transform operator*(const Transform& P) const;
                std::string get_from_frame() const;
                std::string get_to_frame() const;
                Transform inverse() const;
                Point get_point() const;
                RotationMatrix get_rot() const;
                /**  \author cec
                  *  \date Jul 3, 2014, 9:33:16 AM
                  *  \brief Swaps the "to" and "from" frames
                  *  \details This quickfix is done because we need to distinguish
                  *  between reference frame change (same object expressed in a different
                  *  frame) and transform (or mover) (different object in same reference frame)
                  *  \snippet kinematics/unit_tests/src/TransformTest.cpp TransformTest swap_example
                  */
                void swap();

                friend std::ostream& operator<<(std::ostream& os, const Transform& T);

            private:
                Point t;
                RotationMatrix r;
                std::string to_frame;
        };
        std::ostream& operator<<(std::ostream& os, const Transform& T);
        Transform identity(const std::string& frame);
    }
}

#endif /* TRANSFORM_HPP_ */
