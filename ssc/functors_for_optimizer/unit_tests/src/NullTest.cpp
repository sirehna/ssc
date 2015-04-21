/*
 * NullTest.cpp
 *
 * \date 31 janv. 2013, 15:16:28
 *  \author cec
 */

#include "NullTest.hpp"
#include "ssc/functors_for_optimizer/Null.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

using namespace ssc::functors_for_optimizer;

NullTest::NullTest() : a(ssc::random_data_generator::DataGenerator(123))
{
}

NullTest::~NullTest()
{
}

void NullTest::SetUp()
{
}

void NullTest::TearDown()
{
}

TEST_F(NullTest, example)
{
//! [NullTest example]
    const Null n;
//! [NullTest example]
//! [NullTest expected output]
    ASSERT_EQ(0, n.get_lambda()());
//! [NullTest expected output]
}

TEST_F(NullTest, derivative_is_always_zero)
{
    const Null n;
    StateGenerator generate;
    auto x = generate.state("x");
    ASSERT_EQ(0, n.diff(x)->get_lambda()());
}
