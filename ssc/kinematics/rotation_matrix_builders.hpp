/*
 * rotation_matrix_builders.hpp
 *
 *  Created on: 7 avr. 2014
 *      Author: cec
 */

#ifndef ROTATION_MATRIX_BUILDERS_HPP_
#define ROTATION_MATRIX_BUILDERS_HPP_

#include "ssc/kinematics/RotationMatrix.hpp"

namespace ssc
{
    namespace kinematics
    {
        class EulerAngles;

        /** \author cec
         *  \brief 36 different rotation matrices
         *  \details Intrinsic/Extrinsic, axis/angle order convention, Proper Euler/Cardan
         *  \ingroup kinematics
         *  \section ex1 Example
         *  \snippet kinematics/unit_tests/src/rotation_matrix_buildersTest.cpp rotation_matrix_buildersTest example
         *  \section ex2 Expected output
         *  \snippet kinematics/unit_tests/src/rotation_matrix_buildersTest.cpp rotation_matrix_buildersTest expected output
         */

        typedef enum {EXTRINSIC, INTRINSIC} IntrinsicOrExtrinsic;
        typedef enum {CHANGING_ANGLE_ORDER, CHANGING_AXIS_ORDER} OrderConvention;
        template <IntrinsicOrExtrinsic,
                  OrderConvention,
                  int I,
                  int J,
                  int K> RotationMatrix rotation_matrix(const EulerAngles& angles);
        RotationMatrix rot(const double lambda1, const double lambda2, const double lambda3, const double beta);

        template <IntrinsicOrExtrinsic,
                  OrderConvention,
                  int I,
                  int J,
                  int K> EulerAngles euler_angles(const RotationMatrix& R);
    }
}

#endif /* ROTATION_MATRIX_BUILDERS_HPP_ */
