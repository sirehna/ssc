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
#include "extra_test_assertions.hpp"

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

TEST_F(FunctorAlgebraTest, example)
{
//! [FunctorAlgebraTest example]
    auto x = generate.state("x");
    auto y = generate.state("y");
    auto z = generate.state("z");

    auto F1 = pow(x,3);//*(y/z)+z+x*0+0*y;
    auto F2 = y/z;
    auto F3 = z+x*0+0*y;
    auto F4 = x*x*x*(y/z)+z+x*0+0*y;
    std::stringstream ss;
    Serialize s(ss);
    auto d2F4dxdy = F4->diff(x)->diff(y);
    d2F4dxdy->accept(s);

    auto dF4 = F4->diff(x)->diff(y)->diff(z);

    auto f1 = F1->get_lambda();
    auto f2 = F2->get_lambda();
    auto f3 = F3->get_lambda();
    auto f4 = F4->get_lambda();
    auto df4 = dF4->get_lambda();

//! [FunctorAlgebraTest example]
//! [FunctorAlgebraTest expected output]
    const double eps = 1e-12;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **x = a.random<double>().between(-1000,100);
        **y = a.random<double>().between(-1000,100);
        **z = a.random<double>().between(-1000,100);
        ASSERT_DOUBLE_EQ(X*X*X, f1());
        ASSERT_DOUBLE_EQ(Y/Z, f2());
        ASSERT_DOUBLE_EQ(Z, f3());
        ASSERT_SMALL_RELATIVE_ERROR(X*X*X*Y/Z+Z, f4(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(-3*X*X/Z/Z, df4(),eps);
    }
//! [FunctorAlgebraTest expected output]
}

TEST_F(FunctorAlgebraTest, bug_01)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    auto z = generate.state("z");
    std::stringstream ss;
    Serialize s(ss);
    auto f = ((y / z) * ((x * (x + x)) + (x * x)))->diff(y)->get_lambda();
    for (size_t i = 0 ; i < 1 ; ++i)
    {
        **z = a.random<double>().between(-1000,1000)();
        ASSERT_SMALL_RELATIVE_ERROR(3.*pow(**x,2.)/(**z), f(),1E-15);
    }
}

TEST_F(FunctorAlgebraTest, bug_02)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    auto z = generate.state("z");
    auto f = (x*y/z)->diff(x)->diff(y)->diff(z)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **z = a.random<double>().between(-1000,1000)();
        ASSERT_SMALL_RELATIVE_ERROR(-1./((**z)*(**z)), f(),1E-15);
    }
}

TEST_F(FunctorAlgebraTest, bug_03)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    auto z = generate.state("z");

    **x = 3;
    **y = 5;
    **z = 7;
    auto F = (2*x-z*(x+y+3*x)*y);
    auto f = F->get_lambda();
    ASSERT_EQ(2*X-Z*(X+Y+3*X)*Y, f());
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **x = a.random<double>().between(-1000,1000)();
        **y = a.random<double>().between(-1000,1000)();
        **z = a.random<double>().between(-1000,1000)();
        ASSERT_SMALL_RELATIVE_ERROR(2*X-Z*(X+Y+3*X)*Y, f(),1E-8);
    }
}

TEST_F(FunctorAlgebraTest, bug_04)
{
    auto x = generate.state("x");
    X = 3;
    auto F = 3*x;
    auto f = F->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>();
        ASSERT_DOUBLE_EQ(3*X,f());
    }
}

TEST_F(FunctorAlgebraTest, bug_05)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    auto z = generate.state("z");

    **x = 3;
    **y = 500;
    **z = 70000;
    auto F = x+y+3*x;
    auto f = F->get_lambda();
    ASSERT_EQ(X+Y+3*X, f());
}

TEST_F(FunctorAlgebraTest, bug_06)
{
    auto x = generate.state("x");
    auto y = generate.state("y");

    **x = 3;
    **y = 500;
    auto F = 3*(x+y);
    auto f = F->get_lambda();
    ASSERT_EQ(3*(X+Y), f());
}

TEST_F(FunctorAlgebraTest, crash)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    auto f = (x+y)->get_lambda();
    f();
}

TEST_F(FunctorAlgebraTest, bug_07)
{
    auto x = generate.state("x");

    **x = 3;
    auto F = (x-(x+3*x));
    auto f = F->get_lambda();
    ASSERT_EQ(X-(X+3*X), f());
}

TEST_F(FunctorAlgebraTest, bug_08)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    auto z = generate.state("z");

    **x = 3;
    **y = 50;
    auto F = 2*x-z*(x+y+3*x)*y;
    COUT(F->get_type());
    auto f = F->get_lambda();
    ASSERT_EQ(2*X-Z*(X+Y+3*X)*Y, f());
}

TEST_F(FunctorAlgebraTest, bug_09)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    **x = 3;
    **y = 50;
    auto F = x-y*x;
    auto f = F->get_lambda();
    ASSERT_EQ(X-Y*X, f());
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        Y = a.random<double>().between(-1000,1000);
        ASSERT_DOUBLE_EQ(X-Y*X, f());
    }
}

TEST_F(FunctorAlgebraTest, should_be_able_to_substract_a_parameter)
{
    auto x = generate.state("x");
    Parameter p(12);
    auto f = pow(x-p,2)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **x = 13;//a.random<double>();
        //*p = a.random<double>();
        ASSERT_DOUBLE_EQ(pow(**x-*p,2),f());
    }
}
