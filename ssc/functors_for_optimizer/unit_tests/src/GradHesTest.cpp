/*
 * GradHesTest.cpp
 *
 * \date 20 f�vr. 2013, 11:46:48
 *  \author cec
 */

#include "GradHesTest.hpp"
#include "ssc/functors_for_optimizer/GradHes.hpp"
#include "ssc/functors_for_optimizer/FunctionMatrix.hpp"
#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"
#include "ssc/functors_for_optimizer/Sum.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/functors_for_optimizer/Pow.hpp"
#include "ssc/functors_for_optimizer/Serialize.hpp"
#include "ssc/functors_for_optimizer/Grad.hpp"
#include "ssc/functors_for_optimizer/FunctionMatrix.hpp"
#include "ssc/macros/extra_test_assertions.hpp"

#define X1_ (*x1)
#define X2_ (*x2)
#define X3_ (*x3)
#define X4_ (*x4)

#define X1 (x1->get_lambda()())
#define X2 (x2->get_lambda()())
#define X3 (x3->get_lambda()())
#define X4 (x4->get_lambda()())

GradHesTest::GradHesTest() : a(ssc::random_data_generator::DataGenerator(76945)),
                             generate(StateGenerator()),
                             x1(generate.state("x1")),
                             x2(generate.state("x2")),
                             x3(generate.state("x3")),
                             x4(generate.state("x4")),
                             f(x1*x4*(x1+x2+x3)+x3),
                             g(std::vector<NodePtr>())
{
    g.push_back(x1*x2*x3*x4);
    g.push_back(pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2));
}

GradHesTest::~GradHesTest()
{
}

void GradHesTest::SetUp()
{
}

void GradHesTest::TearDown()
{
}

TEST_F(GradHesTest, example)
{
//! [GradHesTest example]
    const StateList states = get_states(f,g);
    Grad grad_f = grad(f, states);
    Parameter sigma_f(1), lambda_1(1), lambda_2(1);
    std::vector<Parameter> lambda;
    lambda.push_back(lambda_1);
    lambda.push_back(lambda_2);
    FunctionMatrix hessian = hes(f,g,sigma_f,lambda,states);
//! [GradHesTest example]
//! [GradHesTest expected output]
//! [GradHesTest expected output]
}

TEST_F(GradHesTest, should_be_able_to_retrieve_states_from_objective_and_constraints)
{
    const StateList states = get_states(f,g);

    ASSERT_EQ(4, states.size());
    ASSERT_EQ(X1, states.at(0)->get_lambda()());
    ASSERT_EQ(X2, states.at(1)->get_lambda()());
    ASSERT_EQ(X3, states.at(2)->get_lambda()());
    ASSERT_EQ(X4, states.at(3)->get_lambda()());
}

TEST_F(GradHesTest, should_be_able_to_compute_the_gradient)
{
    const StateList states = get_states(f);
    Grad grad_f = grad(f, states);
    ASSERT_EQ(4, grad_f.index.size());
    ASSERT_EQ(4, grad_f.values.size());

    const auto df_dx1 = grad_f.values.at(0);
    const auto df_dx2 = grad_f.values.at(1);
    const auto df_dx3 = grad_f.values.at(2);
    const auto df_dx4 = grad_f.values.at(3);
    const double eps = 1e-6;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X1_ = a.random<double>();
        X2_ = a.random<double>();
        X3_ = a.random<double>();
        X4_ = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR(X4*(2*X1+X2+X3), df_dx1(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(X1*X4, df_dx2(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(X1*X4, df_dx3(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(X1*(X1+X2+X3), df_dx4(),eps);
    }
}

TEST_F(GradHesTest, should_be_able_to_compute_the_hessian)
{
    const StateList states = get_states(f,g);
    Parameter sigma_f(1), lambda_1(1), lambda_2(1);
    std::vector<Parameter> lambda;
    lambda.push_back(lambda_1);
    lambda.push_back(lambda_2);
    FunctionMatrix hessian = hes(f,g,sigma_f,lambda,states);
    ASSERT_EQ(10, hessian.values.size());
    ASSERT_EQ(10, hessian.row_index.size());
    ASSERT_EQ(10, hessian.col_index.size());

    const auto d2f_dx1dx1 = hessian.values.at(0);
    const auto d2f_dx2dx1 = hessian.values.at(1);
    const auto d2f_dx2dx2 = hessian.values.at(2);
    const auto d2f_dx3dx1 = hessian.values.at(3);
    const auto d2f_dx3dx2 = hessian.values.at(4);
    const auto d2f_dx3dx3 = hessian.values.at(5);
    const auto d2f_dx4dx1 = hessian.values.at(6);
    const auto d2f_dx4dx2 = hessian.values.at(7);
    const auto d2f_dx4dx3 = hessian.values.at(8);
    const auto d2f_dx4dx4 = hessian.values.at(9);
    const double eps = 1e-6;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X1_ = a.random<double>();
        X2_ = a.random<double>();
        X3_ = a.random<double>();
        X4_ = a.random<double>();
        lambda_1 = a.random<double>();
        lambda_2 = a.random<double>();
        sigma_f  = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR(sigma_f.get_lambda()()*(2*X4)+2*(lambda_2.get_lambda()()), d2f_dx1dx1(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(sigma_f.get_lambda()()*X4+(lambda_1.get_lambda()())*X3*X4, d2f_dx2dx1(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*(lambda_2.get_lambda()()), d2f_dx2dx2(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(sigma_f.get_lambda()()*X4+(lambda_1.get_lambda()())*X2*X4, d2f_dx3dx1(),eps);
        ASSERT_SMALL_RELATIVE_ERROR((lambda_1.get_lambda()())*X1*X4, d2f_dx3dx2(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*(lambda_2.get_lambda()()), d2f_dx3dx3(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(sigma_f.get_lambda()()*(2*X1+X2+X3)+(lambda_1.get_lambda()())*X2*X3, d2f_dx4dx1(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(sigma_f.get_lambda()()*X1+(lambda_1.get_lambda()())*X1*X3, d2f_dx4dx2(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(sigma_f.get_lambda()()*X1+(lambda_1.get_lambda()())*X1*X2, d2f_dx4dx3(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*(lambda_2.get_lambda()()), d2f_dx4dx4(),eps);
    }

}

TEST_F(GradHesTest, should_be_able_to_compute_the_jacobian)
{
    const StateList states = get_states(g);
    FunctionMatrix jacobian = jac(g,states);
    ASSERT_EQ(8, jacobian.values.size());
    ASSERT_EQ(8, jacobian.row_index.size());
    ASSERT_EQ(8, jacobian.col_index.size());
    const auto dg1_dx1 = jacobian.values.at(0);
    const auto dg1_dx2 = jacobian.values.at(1);
    const auto dg1_dx3 = jacobian.values.at(2);
    const auto dg1_dx4 = jacobian.values.at(3);
    const auto dg2_dx1 = jacobian.values.at(4);
    const auto dg2_dx2 = jacobian.values.at(5);
    const auto dg2_dx3 = jacobian.values.at(6);
    const auto dg2_dx4 = jacobian.values.at(7);
    const double eps = 1e-6;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X1_ = a.random<double>();
        X2_ = a.random<double>();
        X3_ = a.random<double>();
        X4_ = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR(X2*X3*X4, dg1_dx1(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(X1*X3*X4, dg1_dx2(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(X1*X2*X4, dg1_dx3(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(X1*X2*X3, dg1_dx4(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*X1, dg2_dx1(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*X2, dg2_dx2(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*X3, dg2_dx3(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*X4, dg2_dx4(), eps);
    }
}

TEST_F(GradHesTest, should_be_able_to_append_states_to_existing_StateList)
{
    StateGenerator generate;
    auto x1 = generate.state("x1");
    auto x2 = generate.state("x2");
    auto x3 = generate.state("x3");
    auto x4 = generate.state("x4");
    auto x5 = generate.state("x5");
    auto x6 = generate.state("x6");
    auto x7 = generate.state("x7");
    auto x8 = generate.state("x8");
    auto l = get_states(x5);
    append(l, x3);
    append(l, x8);
    append(l, x2);
    append(l, x7);
    append(l, x6);
    append(l, x1);
    append(l, x4);

    ASSERT_EQ(8,l.size());
    ASSERT_EQ(*x1,*l.at(0));
    ASSERT_EQ(*x2,*l.at(1));
    ASSERT_EQ(*x3,*l.at(2));
    ASSERT_EQ(*x4,*l.at(3));
    ASSERT_EQ(*x5,*l.at(4));
    ASSERT_EQ(*x6,*l.at(5));
    ASSERT_EQ(*x7,*l.at(6));
    ASSERT_EQ(*x8,*l.at(7));
}
