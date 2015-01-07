/*
 * rotation_matrix_builders_Test.cpp
 *
 *  Created on: 7 avr. 2014
 *      Author: cec
 */

#define _USE_MATH_DEFINES
#include <cmath>
#ifndef M_PI
#define M_PI (4*atan(1.))
#endif
#define PI M_PI

#include "rotation_matrix_builders_Test.hpp"
#include "ssc/kinematics/rotation_matrix_builders.hpp"
#include "ssc/kinematics/EulerAngles.hpp"

#define EPS (1E-10)

using namespace ssc::kinematics;

rotation_matrix_builders_Test::rotation_matrix_builders_Test() : a(ssc::random_data_generator::DataGenerator(545))
{
}

rotation_matrix_builders_Test::~rotation_matrix_builders_Test()
{
}

void rotation_matrix_builders_Test::SetUp()
{
}

void rotation_matrix_builders_Test::TearDown()
{
}

TEST_F(rotation_matrix_builders_Test, can_get_rotation_around_x_axis)
{
    const RotationMatrix R = rot(1,0,0,PI/3);
    ASSERT_DOUBLE_EQ(1, R(0,0));
    ASSERT_DOUBLE_EQ(0, R(1,0));
    ASSERT_DOUBLE_EQ(0, R(2,0));
    ASSERT_DOUBLE_EQ(0, R(0,1));
    ASSERT_DOUBLE_EQ(0.5, R(1,1));
    ASSERT_DOUBLE_EQ(sqrt(3)/2, R(2,1));
    ASSERT_DOUBLE_EQ(0, R(0,2));
    ASSERT_DOUBLE_EQ(-sqrt(3)/2, R(1,2));
    ASSERT_DOUBLE_EQ(0.5, R(2,2));
}

TEST_F(rotation_matrix_builders_Test, can_get_rotation_around_y_axis)
{
    const RotationMatrix R = rot(0,1,0,PI/3);
    ASSERT_DOUBLE_EQ(0.5, R(0,0));
    ASSERT_DOUBLE_EQ(0, R(1,0));
    ASSERT_DOUBLE_EQ(-sqrt(3)/2, R(2,0));
    ASSERT_DOUBLE_EQ(0, R(0,1));
    ASSERT_DOUBLE_EQ(1, R(1,1));
    ASSERT_DOUBLE_EQ(0, R(2,1));
    ASSERT_DOUBLE_EQ(sqrt(3)/2, R(0,2));
    ASSERT_DOUBLE_EQ(0, R(1,2));
    ASSERT_DOUBLE_EQ(0.5, R(2,2));
}

TEST_F(rotation_matrix_builders_Test, can_get_rotation_around_z_axis)
{
    const RotationMatrix R = rot(0,0,1,PI/3);
    ASSERT_DOUBLE_EQ(0.5, R(0,0));
    ASSERT_DOUBLE_EQ(sqrt(3)/2, R(1,0));
    ASSERT_DOUBLE_EQ(0, R(2,0));
    ASSERT_DOUBLE_EQ(-sqrt(3)/2, R(0,1));
    ASSERT_DOUBLE_EQ(0.5, R(1,1));
    ASSERT_DOUBLE_EQ(0, R(2,1));
    ASSERT_DOUBLE_EQ(0, R(0,2));
    ASSERT_DOUBLE_EQ(0, R(1,2));
    ASSERT_DOUBLE_EQ(1, R(2,2));
}

TEST_F(rotation_matrix_builders_Test, example)
{
//! [rotation_matrix_builders_Test example]
    const EulerAngles angles(PI/3, PI/4, PI/6);
    //const EulerAngles angles(PI/2,0,0);
    const RotationMatrix R = rotation_matrix<INTRINSIC, CHANGING_ANGLE_ORDER, 3, 2, 1>(angles);
//! [rotation_matrix_builders_Test example]
//! [rotation_matrix_builders_Test expected output]
    ASSERT_DOUBLE_EQ(sqrt(6)/4, R(0,0));
    ASSERT_DOUBLE_EQ(sqrt(3)/4+sqrt(6)/8, R(1,1));
    ASSERT_DOUBLE_EQ(sqrt(2)/4, R(2,2));
//! [rotation_matrix_builders_Test expected output]
}

TEST_F(rotation_matrix_builders_Test, matrix_to_euler)
{
    for (size_t i = 0 ; i < 10 ; ++i)
    {
        const double phi = a.random<double>().between(-PI,PI);
        const double theta = a.random<double>().between(-PI/2,PI/2);
        const double psi = a.random<double>().between(-PI,PI);
        const EulerAngles input(phi, theta, psi);
        const RotationMatrix R = rotation_matrix<INTRINSIC, CHANGING_ANGLE_ORDER, 3, 2, 1>(input);
        const EulerAngles output = euler_angles<INTRINSIC, CHANGING_ANGLE_ORDER, 3, 2, 1>(R);
        ASSERT_NEAR(phi,   output.phi,   EPS);
        ASSERT_NEAR(theta, output.theta, EPS);
        ASSERT_NEAR(psi,   output.psi,   EPS);
    }
}
