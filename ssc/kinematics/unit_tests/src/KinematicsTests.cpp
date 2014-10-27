/*
 * KinematicsTests.cpp
 *
 *  Created on: 1 avr. 2014
 *      Author: cec
 */

#include "KinematicsTests.hpp"
#include "ssc/kinematics/Kinematics.hpp"
#include "random_kinematics.hpp"
#include "ssc/kinematics/KinematicsException.hpp"
#include "transform_double_equal.hpp"

#define EPS 1E-13

using namespace ssc::kinematics;

KinematicsTests::KinematicsTests() : a(ssc::random_data_generator::DataGenerator(122))
{
}

KinematicsTests::~KinematicsTests()
{
}

void KinematicsTests::SetUp()
{
}

void KinematicsTests::TearDown()
{
}

TEST_F(KinematicsTests, can_add_a_transform_to_a_kinematics_object)
{
    ssc::kinematics::Kinematics k;
    const auto bTa = random_transform(a, a.random<std::string>(), a.random<std::string>());
    k.add(bTa);
}

TEST_F(KinematicsTests, can_retrieve_a_transform)
{
    ssc::kinematics::Kinematics k;
    const std::string from_frame = a.random<std::string>();
    const std::string to_frame = a.random<std::string>();
    const auto bTa = random_transform(a, from_frame, to_frame);
    k.add(bTa);
    const auto transform = k.get(from_frame, to_frame);
    ASSERT_TRUE(double_equal(transform, bTa));
}

TEST_F(KinematicsTests, can_retrieve_inverse_transform)
{
    //! [KinematicsTests get_example]
    ssc::kinematics::Kinematics k;
    const std::string from_frame = a.random<std::string>();
    const std::string to_frame = a.random<std::string>();
    const auto bTa = random_transform(a, from_frame, to_frame);
    k.add(bTa);
    const auto aTb = k.get(to_frame, from_frame);
    //! [KinematicsTests get_example]
    //! [KinematicsTests get_example output]
    ASSERT_TRUE(double_equal(identity(from_frame), aTb*bTa, EPS));
    ASSERT_TRUE(double_equal(identity(to_frame), bTa*aTb, EPS));
    //! [KinematicsTests get_example output]
}

TEST_F(KinematicsTests, throws_if_transform_is_not_computable)
{
    ssc::kinematics::Kinematics k;
    ASSERT_THROW(k.get(a.random<std::string>(),a.random<std::string>()), KinematicsException);
}

TEST_F(KinematicsTests, can_compute_a_transformation_if_necessary_and_feasible)
{
    ssc::kinematics::Kinematics k;

    const auto bTa = random_transform(a, "A", "B");
    const auto cTa = random_transform(a, "A", "C");
    const auto dTb = random_transform(a, "B", "D");
    const auto eTc = random_transform(a, "C", "E");
    const auto fTc = random_transform(a, "C", "F");
    const auto gTd = random_transform(a, "D", "G");
    const auto hTd = random_transform(a, "D", "H");
    const auto iTd = random_transform(a, "D", "I");
    const auto dTe = random_transform(a, "E", "D");

    k.add(bTa);
    k.add(cTa);
    k.add(dTb);
    k.add(eTc);
    k.add(fTc);
    k.add(gTd);
    k.add(hTd);
    k.add(iTd);
    k.add(dTe);

    const auto hTe = k.get("E", "H");

    ASSERT_TRUE(double_equal(hTe, hTd*dTe, EPS));
}

TEST_F(KinematicsTests, can_compute_identity)
{
    ssc::kinematics::Kinematics k;
    const auto bTa = random_transform(a, "A", "B");
    k.add(bTa);
    const auto aTa = k.get("A", "A");
    ASSERT_TRUE(double_equal(identity("A"), aTa, EPS));
}

TEST_F(KinematicsTests, can_add_same_transform_several_times)
{
    ssc::kinematics::Kinematics k;
    const auto bTa = random_transform(a, "A", "B");
    k.add(bTa);
    k.add(bTa);
    k.add(bTa);
    k.add(bTa);
}

TEST_F(KinematicsTests, should_throw_when_computing_transform_between_two_disjoint_frames)
{
    ssc::kinematics::Kinematics k;
    const auto bTa = random_transform(a, "A", "B");
    const auto cTb = random_transform(a, "B", "C");
    const auto dTe = random_transform(a, "E", "D");
    k.add(bTa);
    k.add(cTb);
    k.add(dTe);
    ASSERT_THROW(k.get("A", "E"), KinematicsException);
}

TEST_F(KinematicsTests, should_throw_when_adding_tranform_from_a_frame_to_itself) // Bug detected in IRT simulator
{
    ssc::kinematics::Kinematics k;
    const auto aTa = random_transform(a, "A", "A");
    ASSERT_THROW(k.add(aTa), KinematicsException);
}
