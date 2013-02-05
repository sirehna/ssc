/*
 * DivideTest.cpp
 *
 * \date 1 févr. 2013, 08:50:07
 *  \author cec
 */

#include "DivideTest.hpp"
#include "StateGenerator.hpp"
#include "Divide.hpp"
#include "test_macros.hpp"
#include "Serialize.hpp"

DivideTest::DivideTest() : a(DataGenerator(649731)), generate(StateGenerator())
{
}

DivideTest::~DivideTest()
{
}

void DivideTest::SetUp()
{
}

void DivideTest::TearDown()
{
}

#define X (**x)
#define Y (**y)

TEST_F(DivideTest, example)
{
//! [DivideTest example]
    auto x = generate.state("x");
    auto y = generate.state("y");
    Divide d(x,y);
//! [DivideTest example]
//! [DivideTest expected output]
    auto dv = d.get_value();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>();
        Y = a.random<double>();
        ASSERT_DOUBLE_EQ(X/Y, dv());
    }
//! [DivideTest expected output]
}

TEST_F(DivideTest, DISABLED_derivative)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    Divide d(x,y);
    //COUT(d);
    //d.diff(y);
    COUT(d.diff(y));/*
//! [DivideTest example]
//! [DivideTest expected output]
    auto dv = d.diff(y)->get_value();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **x = a.random<double>();
        **y = a.random<double>();
        ASSERT_DOUBLE_EQ(-X/(Y*Y), dv());
    }*/
}
