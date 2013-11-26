/*
 * almost_equalTest.cpp
 *
 * \date 26 nov. 2013, 08:41:34
 *  \author cec
 */

#include "boost/math/special_functions/next.hpp"
#include "almost_equalTest.hpp"
#include "almost_equal.hpp"

almost_equalTest::almost_equalTest() : a(DataGenerator(7214222))
{
}

almost_equalTest::~almost_equalTest()
{
}

void almost_equalTest::SetUp()
{
}

void almost_equalTest::TearDown()
{
}

TEST_F(almost_equalTest, example)
{
//! [almost_equalTest example]
    ASSERT_TRUE(almost_equal(1,1));
    ASSERT_FALSE(almost_equal(1,2));
//! [almost_equalTest example]
//! [almost_equalTest expected output]
//! [almost_equalTest expected output]
}



