/*
 * SplineVariableStepTest.cpp
 *
 * \date 9 sept. 2013, 10:46:50
 *  \author cec
 */

#include "SplineVariableStepTest.hpp"
#include "SplineVariableStep.hpp"
#include "test_macros.hpp"

SplineVariableStepTest::SplineVariableStepTest() : a(DataGenerator(7777777))
{
}

SplineVariableStepTest::~SplineVariableStepTest()
{
}

void SplineVariableStepTest::SetUp()
{
}

void SplineVariableStepTest::TearDown()
{
}

TEST_F(SplineVariableStepTest, example)
{
//! [SplineVariableStepTest example]
    SplineVariableStep S({1,0,20},{1,4,9});
//! [SplineVariableStepTest example]
//! [SplineVariableStepTest expected output]
    ASSERT_DOUBLE_EQ(1,S.f(1));
    ASSERT_DOUBLE_EQ(4,S.f(0));
    ASSERT_DOUBLE_EQ(9,S.f(20));
//! [SplineVariableStepTest expected output]
}



