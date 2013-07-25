/*
 * for_allTest.cpp
 *
 * \date 19 juil. 2013, 11:52:33
 *  \author cec
 */

#include "for_allTest.hpp"
#include "for_all.hpp"

#include "test_macros.hpp"

for_allTest::for_allTest() : a(DataGenerator(11))
{
}

for_allTest::~for_allTest()
{
}

void for_allTest::SetUp()
{
}

void for_allTest::TearDown()
{
}

TEST_F(for_allTest, can_apply_a_function_to_each_element_in_a_vector)
{
//! [for_allTest example]
    const std::vector<double> v({1,3,2,8,7,1,9});
    std::function<double(const double&)> f = [](const double& x)->double{return x+2;};
    const std::vector<double> ret = for_all(v, f);
//! [for_allTest example]
//! [for_allTest expected output]
    ASSERT_EQ(v.size(), ret.size());
    ASSERT_EQ(3, ret.at(0));
    ASSERT_EQ(5,ret.at(1));
    ASSERT_EQ(4,ret.at(2));
    ASSERT_EQ(10,ret.at(3));
    ASSERT_EQ(9,ret.at(4));
    ASSERT_EQ(3,ret.at(5));
    ASSERT_EQ(11,ret.at(6));
//! [for_allTest expected output]
}



