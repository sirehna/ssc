/*
 * FunctorAlgebraTest.cpp
 *
 * \date 1 févr. 2013, 15:25:03
 *  \author cec
 */

#include "FunctorAlgebraTest.hpp"
#include "FunctorAlgebra.hpp"
#include "Serialize.hpp"
#include "Sum.hpp"
#include "Pow.hpp"
#include "Divide.hpp"
#include "Multiply.hpp"
#include "test_macros.hpp"

FunctorAlgebraTest::FunctorAlgebraTest() : a(DataGenerator(88)), generate(StateGenerator())
{
}

FunctorAlgebraTest::~FunctorAlgebraTest()
{
}

void FunctorAlgebraTest::SetUp()
{
}

void FunctorAlgebraTest::TearDown()
{
}

#define X (**x)
#define Y (**y)
#define Z (**z)

TEST_F(FunctorAlgebraTest, DISABLED_example)
{
//! [FunctorAlgebraTest example]
    auto x = generate.state("x");
    auto y = generate.state("y");
    auto z = generate.state("z");

    auto F1 = pow(x,3);//*(y/z)+z+x*0+0*y;
    auto F2 = y/z;
    auto F3 = z+x*0+0*y;
    auto F4 = x*x*x*(y/z)+z+x*0+0*y;
    auto dF4 = F4->diff(x)->diff(y)->diff(z);
    auto f1 = F1->get_value();
    auto f2 = F2->get_value();
    auto f3 = F3->get_value();
    auto f4 = F4->get_value();
    auto df4 = dF4->get_value();

//! [FunctorAlgebraTest example]
//! [FunctorAlgebraTest expected output]
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **x = a.random<double>();
        **y = a.random<double>();
        **z = a.random<double>();
        ASSERT_DOUBLE_EQ(X*X*X, f1());
        ASSERT_DOUBLE_EQ(Y/Z, f2());
        ASSERT_DOUBLE_EQ(Z, f3());
        ASSERT_DOUBLE_EQ(X*X*X*Y/Z+Z, f4());
        ASSERT_DOUBLE_EQ(-3*X*X/Z/Z, df4());
    }
//! [FunctorAlgebraTest expected output]
}



