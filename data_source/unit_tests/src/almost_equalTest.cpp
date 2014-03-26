/*
 * almost_equalTest.cpp
 *
 * \date 26 nov. 2013, 08:41:34
 *  \author cec
 */

#include <cmath>
#include <limits>

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

TEST_F(almost_equalTest, can_get_a_number_close_to_another)
{
    std::cout << std::setprecision(20);
    for (size_t i = 0 ; i < 10000 ; ++i)
    {
        const double x = a.random<double>().between(-1000,1000);
        ASSERT_LT(x,very_slightly_greater_than(x));
        /*COUT(x);
        COUT(very_slightly_less_than(x));
        COUT(very_slightly_less_than(x)-x);*/

        ASSERT_LT(very_slightly_less_than(x),x);
        ASSERT_DOUBLE_EQ(x,very_slightly_less_than(x));
        ASSERT_DOUBLE_EQ(x,very_slightly_greater_than(x));
    }
}

TEST_F(almost_equalTest, can_get_a_number_not_too_close_to_another)
{
    for (size_t i = 0 ; i < 10000 ; ++i)
    {
        const double x = a.random<double>().between(-1000,1000);
        ASSERT_LT(x,slightly_greater_than(x));
        ASSERT_LT(slightly_less_than(x),x);
    }
}

TEST_F(almost_equalTest, example)
{
//! [almost_equalTest example]
    for (size_t i = 0 ; i < 10000 ; ++i)
    {
        const double x = a.random<double>().between(-1000,1000);
        ASSERT_TRUE(almost_equal(x,x));
        ASSERT_TRUE(almost_equal(x,very_slightly_greater_than(x)));
        ASSERT_DOUBLE_EQ(very_slightly_greater_than(x),x);
        ASSERT_FALSE(almost_equal(slightly_greater_than(x),x));
        ASSERT_DOUBLE_EQ(very_slightly_less_than(x),x);
        ASSERT_FALSE(almost_equal(slightly_less_than(x),x));
        ASSERT_TRUE(almost_equal(x,very_slightly_less_than(x)));
        ASSERT_FALSE(almost_equal(slightly_less_than(x),x));
    }
//! [almost_equalTest example]
//! [almost_equalTest expected output]
//! [almost_equalTest expected output]
}

double almost_equalTest::very_slightly_less_than(const double x) const
{
    return nextafter(x,-std::numeric_limits<double>::max());
}

double almost_equalTest::very_slightly_greater_than(const double x) const
{
    return nextafter(x,std::numeric_limits<double>::max());
}

double almost_equalTest::slightly_less_than(double x) const
{
    for (size_t i = 0 ; i < 5 ; ++i) x = very_slightly_less_than(x);
    return x;
}

double almost_equalTest::slightly_greater_than(double x) const
{
    for (size_t i = 0 ; i < 5 ; ++i) x = very_slightly_greater_than(x);
    return x;
}
