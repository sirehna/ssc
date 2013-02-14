/*
 * NullTest.cpp
 *
 * \date 31 janv. 2013, 15:16:28
 *  \author cec
 */

#include "NullTest.hpp"
#include "Null.hpp"
#include "StateGenerator.hpp"
#include "test_macros.hpp"

NullTest::NullTest() : a(DataGenerator(123))
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
