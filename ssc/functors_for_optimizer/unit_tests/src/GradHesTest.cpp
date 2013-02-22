/*
 * GradHesTest.cpp
 *
 * \date 20 févr. 2013, 11:46:48
 *  \author cec
 */

#include "GradHesTest.hpp"
#include "GradHes.hpp"
#include "FunctorAlgebra.hpp"
#include "StateGenerator.hpp"
#include "Sum.hpp"
#include "Multiply.hpp"
#include "Pow.hpp"
#include "Serialize.hpp"
#include "Grad.hpp"
#include "FunctionMatrix.hpp"
#include "extra_test_assertions.hpp"

GradHesTest::GradHesTest() : a(DataGenerator(76945))
{
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
    StateGenerator generate;
    auto x1 = generate.state("x1");
    auto x2 = generate.state("x2");
    auto x3 = generate.state("x3");
    auto x4 = generate.state("x4");
    auto f = x1*x4*(x1+x2+x3)+x3;
    std::vector<NodePtr> g;
    g.push_back(x1*x2*x3*x4);
    g.push_back(pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2));
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
    StateGenerator generate;
    auto x1 = generate.state("x1");
    auto x2 = generate.state("x2");
    auto x3 = generate.state("x3");
    auto x4 = generate.state("x4");
    auto f = x1*x4*(x1+x2+x3)+x3;
    std::vector<NodePtr> g;
    g.push_back(x1*x2*x3*x4);
    g.push_back(pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2));
    const StateList states = get_states(f,g);

    ASSERT_EQ(4, states.size());
    ASSERT_EQ(*x1, *states.at(0));
    ASSERT_EQ(*x2, *states.at(1));
    ASSERT_EQ(*x3, *states.at(2));
    ASSERT_EQ(*x4, *states.at(3));
}

TEST_F(GradHesTest, should_be_able_to_compute_the_gradient)
{
    StateGenerator generate;
    auto x1 = generate.state("x1");
    auto x2 = generate.state("x2");
    auto x3 = generate.state("x3");
    auto x4 = generate.state("x4");
    auto f = x1*x4*(x1+x2+x3)+x3;
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
        **x1 = a.random<double>();
        **x2 = a.random<double>();
        **x3 = a.random<double>();
        **x4 = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR((**x4)*(2*(**x1)+**x2+**x3), df_dx1(),eps);
        ASSERT_SMALL_RELATIVE_ERROR((**x1)*(**x4), df_dx2(),eps);
        ASSERT_SMALL_RELATIVE_ERROR((**x1)*(**x4), df_dx3(),eps);
        ASSERT_SMALL_RELATIVE_ERROR((**x1)*(**x1+**x2+**x3), df_dx4(),eps);
    }
}

TEST_F(GradHesTest, should_be_able_to_compute_the_hessian)
{
    StateGenerator generate;
    auto x1 = generate.state("x1");
    auto x2 = generate.state("x2");
    auto x3 = generate.state("x3");
    auto x4 = generate.state("x4");
    auto f = x1*x4*(x1+x2+x3)+x3;
    std::vector<NodePtr> g;
    g.push_back(x1*x2*x3*x4);
    g.push_back(pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2));
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
        **x1 = a.random<double>();
        **x2 = a.random<double>();
        **x3 = a.random<double>();
        **x4 = a.random<double>();
        *lambda_1 = a.random<double>();
        *lambda_2 = a.random<double>();
        *sigma_f  = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR(*sigma_f*(2*(**x4))+2*(*lambda_2), d2f_dx1dx1(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(*sigma_f*(**x4)+(*lambda_1)*(**x3)*(**x4), d2f_dx2dx1(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*(*lambda_2), d2f_dx2dx2(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(*sigma_f*(**x4)+(*lambda_1)*(**x2)*(**x4), d2f_dx3dx1(),eps);
        ASSERT_SMALL_RELATIVE_ERROR((*lambda_1)*(**x1)*(**x4), d2f_dx3dx2(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*(*lambda_2), d2f_dx3dx3(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(*sigma_f*(2*(**x1)+(**x2)+(**x3))+(*lambda_1)*(**x2)*(**x3), d2f_dx4dx1(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(*sigma_f*(**x1)+(*lambda_1)*(**x1)*(**x3), d2f_dx4dx2(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(*sigma_f*(**x1)+(*lambda_1)*(**x1)*(**x2), d2f_dx4dx3(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*(*lambda_2), d2f_dx4dx4(),eps);
    }

}

TEST_F(GradHesTest, should_be_able_to_compute_the_jacobian)
{
    StateGenerator generate;
    auto x1 = generate.state("x1");
    auto x2 = generate.state("x2");
    auto x3 = generate.state("x3");
    auto x4 = generate.state("x4");
    std::vector<NodePtr> g;
    g.push_back(x1*x2*x3*x4);
    g.push_back(pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2));
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
        **x1 = a.random<double>();
        **x2 = a.random<double>();
        **x3 = a.random<double>();
        **x4 = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR((**x2)*(**x3)*(**x4), dg1_dx1(), eps);
        ASSERT_SMALL_RELATIVE_ERROR((**x1)*(**x3)*(**x4), dg1_dx2(), eps);
        ASSERT_SMALL_RELATIVE_ERROR((**x1)*(**x2)*(**x4), dg1_dx3(), eps);
        ASSERT_SMALL_RELATIVE_ERROR((**x1)*(**x2)*(**x3), dg1_dx4(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*(**x1), dg2_dx1(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*(**x2), dg2_dx2(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*(**x3), dg2_dx3(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*(**x4), dg2_dx4(), eps);
    }
}

