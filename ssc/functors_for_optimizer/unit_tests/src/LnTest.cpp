/*
 * LnTest.cpp
 *
 * \date 1 févr. 2013, 12:28:55
 *  \author cec
 */

#include "LnTest.hpp"
#include <cmath>
#include "Ln.hpp"
#include "test_macros.hpp"

LnTest::LnTest() : a(DataGenerator(24)), generate(StateGenerator())
{
}

LnTest::~LnTest()
{
}

void LnTest::SetUp()
{
}

void LnTest::TearDown()
{
}

TEST_F(LnTest, example)
{
//! [LnTest example]
    auto x = generate.state("x");
    Ln l(x);
    auto v = l.get_lambda();
//! [LnTest example]
//! [LnTest expected output]
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *x = a.random<double>().greater_than(0);
        ASSERT_DOUBLE_EQ(log(x->get_lambda()()), v());
    }
//! [LnTest expected output]
}

TEST_F(LnTest, derivative)
{
    auto x = generate.state("x");
    Ln l(x);
    auto v = l.diff(x)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *x = a.random<double>().greater_than(0);
        ASSERT_DOUBLE_EQ(1/(x->get_lambda()()), v());
    }
}



