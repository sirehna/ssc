/*
 * TypeCoercionTest.cpp
 *
 * \date 17 juin 2013, 14:54:12
 *  \author cec
 */

#include "TypeCoercionTest.hpp"
#include "TypeCoercion.hpp"

TypeCoercionTest::TypeCoercionTest() : a(DataGenerator(1))
{
}

TypeCoercionTest::~TypeCoercionTest()
{
}

void TypeCoercionTest::SetUp()
{
}

void TypeCoercionTest::TearDown()
{
}

TEST_F(TypeCoercionTest, can_coerce_doubles_to_doubles)
{
    const double d1 = a.random<double>();
    const double d2 = a.random<double>();
    const double d3 = a.random<double>();
    std::list<double> v;
    coerce(v,d1);
    coerce(v,d2);
    coerce(v,d3);
    ASSERT_EQ(3, v.size());
    ASSERT_DOUBLE_EQ(d1, v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(d2, v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(d3, v.front());v.pop_front();
}

TEST_F(TypeCoercionTest, can_coerce_vector_of_doubles_to_doubles)
{
    const std::vector<double> v1 = a.random_vector_of<double>().of_size(3);
    const std::vector<double> v2 = a.random_vector_of<double>().of_size(5);
    const std::vector<double> v3 = a.random_vector_of<double>().of_size(8);
    std::list<double> v;
    coerce(v,v1);
    coerce(v,v2);
    coerce(v,v3);
    ASSERT_EQ(16, v.size());
    ASSERT_DOUBLE_EQ(v1.at(0), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v1.at(1), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v1.at(2), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v2.at(0), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v2.at(1), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v2.at(2), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v2.at(3), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v2.at(4), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v3.at(0), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v3.at(1), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v3.at(2), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v3.at(3), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v3.at(4), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v3.at(5), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v3.at(6), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v3.at(7), v.front());
}

TEST_F(TypeCoercionTest, can_coerce_different_types_to_doubles)
{
    const std::vector<int> v1 = a.random_vector_of<int>().of_size(3);
    const size_t v2 = a.random<size_t>();
    const bool v3 = a.random<bool>();
    const std::vector<float> v4 = a.random_vector_of<float>().of_size(4);
    std::list<double> v;
    coerce(v,v1);
    coerce(v,v2);
    coerce(v,v3);
    coerce(v,v4);
    ASSERT_EQ(9, v.size());
    ASSERT_DOUBLE_EQ(v1.at(0), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v1.at(1), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v1.at(2), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v2, v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v3, v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v4.at(0), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v4.at(1), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v4.at(2), v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(v4.at(3), v.front());v.pop_front();
}

// Lets define a non-arithmetic type
struct S
{
    S(const double a_, const double b_):a(a_),b(b_) {}
    double a;
    double b;
};

// Then define a coercion function for it (note that this is an overload, not a
// specialization because specialization of function templates should generally
// be avoided)
void coerce(std::list<double>& ret, const S& thing_to_convert);
void coerce(std::list<double>& ret, const S& thing_to_convert)
{
    ret.push_back(thing_to_convert.a);
    ret.push_back(thing_to_convert.b);
}

TEST_F(TypeCoercionTest, can_define_coercion_for_non_arithmetic_types)
{
    std::list<double> v;

    const double a_ = a.random<double>();
    const double b_ = a.random<double>();
    coerce(v, S(a_,b_));
    ASSERT_DOUBLE_EQ(a_,v.front());v.pop_front();
    ASSERT_DOUBLE_EQ(b_,v.front());v.pop_front();
}

