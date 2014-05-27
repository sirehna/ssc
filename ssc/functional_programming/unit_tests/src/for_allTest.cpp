/*
 * for_allTest.cpp
 *
 * \date 19 juil. 2013, 11:52:33
 *  \author cec
 */

#include "for_allTest.hpp"
#include "for_all.hpp"

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
    const auto ret = for_all(v, f);
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

TEST_F(for_allTest, works_with_simplified_syntax)
{
    const std::vector<double> v({1,3,2,8,7,1,9});
    const auto ret = for_all(v, [](const double x){return x+2;});
    ASSERT_EQ(v.size(), ret.size());
    ASSERT_EQ(3, ret.at(0));
    ASSERT_EQ(5,ret.at(1));
    ASSERT_EQ(4,ret.at(2));
    ASSERT_EQ(10,ret.at(3));
    ASSERT_EQ(9,ret.at(4));
    ASSERT_EQ(3,ret.at(5));
    ASSERT_EQ(11,ret.at(6));


}

TEST_F(for_allTest, throws_if_supplied_two_vectors_of_different_lengths)
{
    const size_t n1 = a.random<size_t>().no().greater_than(10000);
    const std::vector<double> v1 = a.random_vector_of<double>().of_size(n1);
    const size_t n2 = a.random<size_t>().no().greater_than(10000).but_not(n1);
    const std::vector<double> v2 = a.random_vector_of<double>().of_size(n2);
    ASSERT_THROW(for_all(v1,v2,std::plus<double>()), For_all_exception);
}

TEST_F(for_allTest, can_apply_function_of_two_arguments_to_all_elements_in_pair_of_vectors)
{
    const std::vector<double> v1({1,3,2,8 ,7  ,1,9});
    const std::vector<double> v2({4,5,8,65,814,2,4});
    const std::vector<double> ret = for_all(v1,v2,std::plus<double>());
    ASSERT_EQ(7, ret.size());
    ASSERT_EQ(5,ret.at(0));
    ASSERT_EQ(8,ret.at(1));
    ASSERT_EQ(10,ret.at(2));
    ASSERT_EQ(73,ret.at(3));
    ASSERT_EQ(821,ret.at(4));
    ASSERT_EQ(3,ret.at(5));
    ASSERT_EQ(13,ret.at(6));
}
