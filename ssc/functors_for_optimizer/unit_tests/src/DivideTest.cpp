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

DivideTest::DivideTest() : a(DataGenerator(649731)), generate(StateGenerator()), x(generate.state("x")), y(generate.state("y"))
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

#define X (*x)
#define Y (*y)
#define X_ (x->get_lambda()())
#define Y_ (y->get_lambda()())

TEST_F(DivideTest, example)
{
//! [DivideTest example]
    Divide d(x,y);
//! [DivideTest example]
//! [DivideTest expected output]
    auto dv = d.get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>();
        Y = a.random<double>();
        ASSERT_DOUBLE_EQ(X_/Y_, dv());
    }
//! [DivideTest expected output]
}

TEST_F(DivideTest, derivative)
{
    Divide d(x,y);
    COUT(d.diff(y));
//! [DivideTest example]
//! [DivideTest expected output]
    auto dv = d.diff(y)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>();
        Y = a.random<double>();
        ASSERT_NEAR(-X_/(Y_*Y_), dv(), 1E-10);
    }
}

TEST_F(DivideTest, bug_derive_a_double_division)
{
    Divide d(DividePtr(new Divide(x,y)),y);
    auto dv = d.diff(y)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        Y = a.random<double>().between(-1000,1000);
        ASSERT_DOUBLE_EQ(-2.*(X_)/pow(Y_,3),dv());
    }
}
