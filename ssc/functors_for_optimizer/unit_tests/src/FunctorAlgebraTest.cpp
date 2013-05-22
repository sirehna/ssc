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
#include "SerializeReversePolish.hpp"

#include "Cos.hpp"
#include "Sin.hpp"
#include "Constant.hpp"
#include <cmath>
#include <sstream>

#define PI (4.*atan(1.))
#define EPS 1e-8



FunctorAlgebraTest::FunctorAlgebraTest() : a(DataGenerator(88)), generate(StateGenerator()),
x(generate.state("x")),
y(generate.state("y")),
z(generate.state("z"))
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
        ASSERT_SMALL_RELATIVE_ERROR(X*X*X, f1(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(Y/Z, f2(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(Z, f3(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(X*X*X*Y/Z+Z, f4(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(-3*X*X/Z/Z, df4(),eps);
    }
//! [FunctorAlgebraTest expected output]
}

TEST_F(FunctorAlgebraTest, bug_01)
{
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
    auto f = (x*y/z)->diff(x)->diff(y)->diff(z)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **z = a.random<double>().between(-1000,1000)();
        ASSERT_SMALL_RELATIVE_ERROR(-1./((**z)*(**z)), f(),1E-14);
    }
}

TEST_F(FunctorAlgebraTest, bug_03)
{
    X = 3;
    Y = 5;
    Z = 7;
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
    X = 3;
    auto F = 3*x;
    auto f = F->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR(3*X,f(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_05)
{
    X = 3;
    Y = 500;
    Z = 70000;
    auto F = x+y+3*x;
    auto f = F->get_lambda();
    ASSERT_EQ(X+Y+3*X, f());
}

TEST_F(FunctorAlgebraTest, bug_06)
{
    X = 3;
    Y = 500;
    auto F = 3*(x+y);
    auto f = F->get_lambda();
    ASSERT_EQ(3*(X+Y), f());
}

TEST_F(FunctorAlgebraTest, crash)
{
    auto f = (x+y)->get_lambda();
    f();
}

TEST_F(FunctorAlgebraTest, bug_07)
{
    X = 3;
    auto F = (x-(x+3*x));
    SerializeReversePolish s(std::cout);
    F->accept(s);std::cout<<std::endl;
    auto f = F->get_lambda();
    ASSERT_EQ(X-(X+3*X), f());
}

TEST_F(FunctorAlgebraTest, bug_08)
{
    auto f = (2*x-z*(x+y+3*x)*y)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        Y = a.random<double>().between(-1000,1000);
        Z = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(2*X-Z*(X+Y+3*X)*Y, f(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_09)
{
    X = 3;
    Y = 50;
    auto f = (x-y*x)->get_lambda();
    ASSERT_EQ(X-Y*X, f());
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        Y = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(X-Y*X, f(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, should_be_able_to_substract_a_parameter)
{
    Parameter p(12);
    auto f = pow(x-p,2)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **x = a.random<double>();
        *p = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR(pow(**x-*p,2),f(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_10)
{
    const auto F = 1-x;
    const auto f = F->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(1-X, f(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_11)
{
    X = 3;
    const auto F0 = x-1;
    const auto F05 = pow(F0,5);
    const auto f0 = F0->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(X-1, f0(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_12)
{
    const auto F = 100*pow(y-pow(x,2),2)+pow(1.-x,2);
    const auto f = F->get_lambda();
    const auto df_dx = F->diff(x)->get_lambda();
    const auto df_dy = F->diff(y)->get_lambda();
    const auto d2f_dx2 = F->diff(x)->diff(x)->get_lambda();
    const auto d2f_dy2 = F->diff(y)->diff(y)->get_lambda();
    const auto d2f_dxy = F->diff(x)->diff(y)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        Y = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(100*pow(Y-X*X,2)+pow(1.-X,2), f(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(-400*X*(Y-X*X)+2*(X-1), df_dx(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(200*(Y-X*X), df_dy(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(400*(3*X*X-Y)+2, d2f_dx2(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(200, d2f_dy2(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(-400*X, d2f_dxy(),EPS);
    }

}


TEST_F(FunctorAlgebraTest, bug_13)
{
    const auto F = x-1;
    const auto f = F->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(X-1, f(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_14)
{
    const auto F = 100*pow(y-pow(x,2),2)+pow(x-1,2);
    const auto rosenbrock_banana_function = F->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        Y = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(100*pow(Y-X*X,2)+pow(X-1,2), rosenbrock_banana_function(),1E-8);
    }
}

TEST_F(FunctorAlgebraTest, bug_15)
{
    const auto F = 100*pow(y-pow(x,2),2)+pow(x-1,2);
    const auto f = F->get_lambda();
    const auto df_dx = F->diff(x)->get_lambda();
    const auto df_dy = F->diff(y)->get_lambda();
    const auto d2f_dx2 = F->diff(x)->diff(x)->get_lambda();
    const auto d2f_dy2 = F->diff(y)->diff(y)->get_lambda();
    const auto d2f_dxy = (-400 * (y - (pow(x, 2))) * x + 2 * (x - 1))->diff(y)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        Y = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(100*pow(Y-X*X,2)+pow(X-1,2), f(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(-400*X*(Y-X*X)+2*(X-1), df_dx(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(200*(Y-X*X), df_dy(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(400*(3*X*X-Y)+2, d2f_dx2(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(200, d2f_dy2(),EPS);
        ASSERT_SMALL_RELATIVE_ERROR(-400*X, d2f_dxy(),EPS);
    }

}

TEST_F(FunctorAlgebraTest, bug_16)
{
    const auto f = pow(y-pow(x,2),2)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        Y = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(pow(Y-X*X,2), f(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_17)
{
    const auto f = ((-1)*pow(x,2))->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(-pow(X,2), f(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_18)
{
    const auto df_dx = ((-1)*pow(x,2))->diff(x)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(-2*X, df_dx(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_19)
{
    const auto df_dx = (pow(y-pow(x,2),2))->diff(x)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        Y = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(-4*X*(Y-X*X), df_dx(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_20)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        const auto f = (x+2*(x-1))->get_lambda();
        ASSERT_SMALL_RELATIVE_ERROR(X+2*(X-1), f(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_21)
{
    const auto df_dx = (x*(y-x*x))->diff(x)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        Y = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(-3*X*X+Y, df_dx(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_22)
{
    const auto F = 2*(x-1);
    const auto f = F->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(2*(X-1), f(),EPS);
    }
}


TEST_F(FunctorAlgebraTest, bug_23)
{
    const auto F = 2*(pow(x,2)+x);
    const auto df_dx = F->diff(x)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(4*X+2, df_dx(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_24)
{
    const auto f = (-400 * (y - (pow(x, 2))) * x + 2 * (x - 1))->diff(y)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        Y = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(-400*X, f(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_25)
{
	const auto f = (400*(y - x) * x)->diff(y)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        Y = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(400*X, f(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_26)
{
    const auto d2f_dxy = pow(y-pow(x,2),2)->diff(x)->diff(y)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        Y = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(-4*X, d2f_dxy(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_27)
{
    const auto d2f_dx2 = pow(y-pow(x,2),2)->diff(x)->diff(x)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        Y = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(4*(3*X*X-Y), d2f_dx2(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_28)
{
    const auto df_dx = (-1.*pow(x,2))->diff(x)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(-2.*X, df_dx(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_29)
{
    const auto dF_dx = pow(y-pow(x,2),2)->diff(x);
    const auto df_dx = dF_dx->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        Y = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(4*X*(X*X-Y), df_dx(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_30)
{
    const auto d2F_dx2 = ((4*x)*(pow(x,2)-y))->diff(x);
    const auto d2f_dx2 = d2F_dx2->get_lambda();

    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        Y = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(4*(3*X*X-Y), d2f_dx2(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_31)
{
    std::vector<NodePtr> v;
    v.push_back(2*x);
    Multiply multiply(v);
    std::vector<NodePtr> vv;
    multiply.multiply_by(-1);
    vv.push_back(multiply.clone());
    Sum sum(vv);
    auto f = sum.diff(x)->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>().between(-1000,1000);
        Y = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(-2, f(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_32)
{
    auto x1 = generate.state("x1");
    auto x2 = generate.state("x2");
    auto x3 = generate.state("x3");
    auto x4 = generate.state("x4");
    auto f = (pow(x1,2)*Cos(x3))+(pow(x2,2)*Cos(x4));
    auto df = f->diff(x1);

    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        (**x1) = a.random<double>().between(-1000,1000);
        (**x2) = a.random<double>().between(-1000,1000);
        (**x3) = a.random<double>().between(-1000,1000);
        (**x4) = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(2*(**x1)*cos(**x3), df->get_lambda()(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_33)
{
    auto x1 = generate.state("x1");
    auto x2 = generate.state("x2");
    auto x3 = generate.state("x3");
    auto x4 = generate.state("x4");
    auto f = pow(x2,2)*Cos(x4);
    auto df = f->diff(x1);

    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        (**x1) = a.random<double>().between(-1000,1000);
        (**x2) = a.random<double>().between(-1000,1000);
        (**x3) = a.random<double>().between(-1000,1000);
        (**x4) = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(0, df->get_lambda()(),EPS);
    }
}

TEST_F(FunctorAlgebraTest, bug_34)
{
    auto x1 = generate.state("x1");
    auto x3 = generate.state("x3");
    auto f = pow(x1,2)*Cos(x3);
    auto df = f->diff(x3);

    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        (**x1) = a.random<double>().between(-1000,1000);
        (**x3) = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(-pow((**x1),2)*sin(**x3), df->get_lambda()(),EPS);

    }
}

TEST_F(FunctorAlgebraTest, bug_35)
{
    auto x1 = generate.state("x1");
    auto x3 = generate.state("x3");

    auto f1 = Sin(x3).clone();
    f1->multiply_by(-1);
    auto f = pow(x1,2)*f1;


    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        (**x1) = a.random<double>().between(-1000,1000);
        (**x3) = a.random<double>().between(-1000,1000);
        ASSERT_SMALL_RELATIVE_ERROR(-pow((**x1),2)*sin(**x3), f->get_lambda()(),EPS);
    }
}
