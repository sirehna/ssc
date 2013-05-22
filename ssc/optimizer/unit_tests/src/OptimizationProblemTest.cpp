/*
 * OptimizationProblemTest.cpp
 *
 * \date 21 févr. 2013, 10:15:03
 *  \author cec
 */

#include "OptimizationProblemTest.hpp"
#include "OptimizationProblem.hpp"
#include "GradHes.hpp"
#include "Grad.hpp"
#include "FunctionMatrix.hpp"
#include "extra_test_assertions.hpp"
#include "Serialize.hpp"
#include "Cos.hpp"
#include "Sin.hpp"

#include "test_macros.hpp"

#include <cmath>
#define PI (4.*atan(1.))

#define X1 (**x1)
#define X2 (**x2)
#define X3 (**x3)
#define X4 (**x4)

OptimizationProblemTest::OptimizationProblemTest() : a(DataGenerator(1)),
                                                     generate(StateGenerator()),
                                                     x1(generate.state("x1")),
                                                     x2(generate.state("x2")),
                                                     x3(generate.state("x3")),
                                                     x4(generate.state("x4"))
{
}

OptimizationProblemTest::~OptimizationProblemTest()
{
}

void OptimizationProblemTest::SetUp()
{
}

void OptimizationProblemTest::TearDown()
{
}

TEST_F(OptimizationProblemTest, example)
{
//! [OptimizationProblemTest example]
    OptimizationProblem hs71;
//! [OptimizationProblemTest example]
//! [OptimizationProblemTest expected output]
    hs71.minimize(x1*x4*(x1+x2+x3)+x3)
        .subject_to(25,x1*x2*x3*x4)
        .subject_to(40,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),40);
//! [OptimizationProblemTest expected output]
}

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_list_of_states)
{
    OptimizationProblem problem;
    problem.minimize(x1*x4)
        .subject_to(25,x1*x3)
        .subject_to(40,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),40);

    const StateList states = problem.get_states();

    ASSERT_EQ(4, states.size());
    ASSERT_EQ(*x1, *states.at(0));
    ASSERT_EQ(*x2, *states.at(1));
    ASSERT_EQ(*x3, *states.at(2));
    ASSERT_EQ(*x4, *states.at(3));
}

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_objective_function)
{
    OptimizationProblem hs71;
    hs71.minimize(x1*x4*(x1+x2+x3)+x3);
    const auto objective_function = hs71.get_objective_function();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X1 = a.random<double>();
        X2 = a.random<double>();
        X3 = a.random<double>();
        X4 = a.random<double>();
        ASSERT_DOUBLE_EQ(X1*X4*(X1+X2+X3)+X3, objective_function());
    }
}

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_constraint_bounds)
{
    double g_l[2];
    double g_u[2];
    OptimizationProblem hs71;
    hs71.minimize(x1*x4*(x1+x2+x3)+x3)
        .subject_to(25,x1*x2*x3*x4)
        .subject_to(40,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),40);
    hs71.get_constraint_bounds(2, g_l, g_u);
    ASSERT_EQ(25, g_l[0]);
    ASSERT_EQ(40, g_l[1]);
    ASSERT_EQ(INFTY, g_u[0]);
    ASSERT_EQ(40, g_u[1]);
}

TEST_F(OptimizationProblemTest, method_to_retrieve_constraint_bounds_should_throw_if_any_pointers_are_null)
{
    double g_l[2];
    double g_u[2];
    OptimizationProblem pb;
    ASSERT_THROW(pb.get_constraint_bounds(2, NULL, g_u), OptimizationProblemException);
    ASSERT_THROW(pb.get_constraint_bounds(2, g_l, NULL), OptimizationProblemException);
    ASSERT_THROW(pb.get_constraint_bounds(2, NULL, NULL), OptimizationProblemException);
}

TEST_F(OptimizationProblemTest, should_be_able_to_set_and_retrieve_state_bounds_bug)
{
    OptimizationProblem pb;
    pb.minimize(x1*x2);
    pb.bound_state(1,x1,2);
    pb.bound_state(3,x2,4);
    const size_t nb_of_states = 2;
    double x_l[nb_of_states];
    double x_u[nb_of_states];
    pb.get_state_bounds(nb_of_states,x_l,x_u);
    ASSERT_EQ(1, x_l[0]);
    ASSERT_EQ(2, x_u[0]);
    ASSERT_EQ(3, x_l[1]);
    ASSERT_EQ(4, x_u[1]);
}

TEST_F(OptimizationProblemTest, should_be_able_to_set_and_retrieve_state_bounds_bug_02)
{
    OptimizationProblem pb;
    pb.minimize(x1*x4*(x1+x2+x3)+x3).bound_state(1,x1,2);
    const size_t nb_of_states = 4;
    double x_l[nb_of_states];
    double x_u[nb_of_states];
    pb.get_state_bounds(nb_of_states,x_l,x_u);
    ASSERT_EQ(1, x_l[0]);
}

TEST_F(OptimizationProblemTest, should_be_able_to_set_and_retrieve_state_bounds)
{
    OptimizationProblem hs71;

    hs71.minimize(x1*x4*(x1+x2+x3)+x3)
        .bound_state(1,x1,2)
        .bound_state(x2,3)
        .bound_state(4,x3)
        .bound_state(6,x4,7);

    double x_l[4];
    double x_u[4];
    hs71.get_state_bounds(4,x_l,x_u);
    ASSERT_EQ(1, x_l[0]);
    ASSERT_EQ(-INFTY, x_l[1]);
    ASSERT_EQ(4, x_l[2]);
    ASSERT_EQ(6, x_l[3]);
    ASSERT_EQ(2, x_u[0]);
    ASSERT_EQ(3, x_u[1]);
    ASSERT_EQ(INFTY, x_u[2]);
    ASSERT_EQ(7, x_u[3]);
}

TEST_F(OptimizationProblemTest, should_throw_if_attempting_to_retrieve_state_bounds_with_an_invalid_number_of_states)
{
    OptimizationProblem pb;
    pb.minimize(x1*x4*(x1+x2+x3)+x3);
    double x_l[4];
    double x_u[4];
    ASSERT_THROW(pb.get_state_bounds(a.random<size_t>().but_not(4),x_l,x_u), OptimizationProblemException);
    ASSERT_THROW(pb.get_state_bounds(4,NULL,x_u), OptimizationProblemException);
    ASSERT_THROW(pb.get_state_bounds(4,NULL,NULL), OptimizationProblemException);
    ASSERT_THROW(pb.get_state_bounds(4,x_l,NULL), OptimizationProblemException);
    ASSERT_NO_THROW(pb.get_state_bounds(4,x_l,x_u));
}

TEST_F(OptimizationProblemTest, should_throw_if_attempting_to_set_the_same_constraint_twice)
{
    OptimizationProblem problem;
    problem.subject_to(25,x1*x3);
    ASSERT_THROW(problem.subject_to(x1*x3,25), OptimizationProblemException);
}

TEST_F(OptimizationProblemTest, should_throw_if_attempting_to_set_the_same_state_bounds_twice)
{
    OptimizationProblem problem;
    problem.minimize(pow(x1-2,2));
    problem.bound_state(1,x1,2);
    ASSERT_THROW(problem.bound_state(x1,2), OptimizationProblemException);
}

TEST_F(OptimizationProblemTest, different_ways_to_specify_constraint_bounds)
{
    OptimizationProblem problem;
    problem.minimize(x1*x4)
           .subject_to(25,x1*x3)
           .subject_to(40,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),40)
           .subject_to(x2*x3,50);
    double g_l[3];
    double g_u[3];
    problem.get_constraint_bounds(3, g_l, g_u);
    ASSERT_EQ(25, g_l[0]);
    ASSERT_EQ(40, g_l[1]);
    ASSERT_EQ(-INFTY, g_l[2]);
    ASSERT_EQ(INFTY, g_u[0]);
    ASSERT_EQ(40, g_u[1]);
    ASSERT_EQ(50, g_u[2]);
}

TEST_F(OptimizationProblemTest, should_be_able_to_specify_constraints_bounds_with_parameters)
{
    OptimizationProblem problem;
    Parameter p1, p2, p3, p4;
    problem.minimize(x1*x4)
           .subject_to(p1,x1*x3)
           .subject_to(p2,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),p3)
           .subject_to(x2*x3,p4);
    double g_l[3];
    double g_u[3];
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        problem.get_constraint_bounds(3, g_l, g_u);
        ASSERT_DOUBLE_EQ(*p1, g_l[0]);
        ASSERT_DOUBLE_EQ(*p2, g_l[1]);
        ASSERT_EQ(-INFTY, g_l[2]);
        ASSERT_EQ(INFTY, g_u[0]);
        ASSERT_DOUBLE_EQ(*p3, g_u[1]);
        ASSERT_DOUBLE_EQ(*p4, g_u[2]);
    }
}

TEST_F(OptimizationProblemTest, should_throw_if_attempting_to_specify_bounds_to_inexistant_state)
{
    OptimizationProblem problem;
    problem.minimize(x1*x2);
    ASSERT_THROW(problem.bound_state(1,x3,2), OptimizationProblemException);
    ASSERT_THROW(problem.bound_state(1,x3), OptimizationProblemException);
    ASSERT_THROW(problem.bound_state(x3,2), OptimizationProblemException);
}

TEST_F(OptimizationProblemTest, should_be_able_to_specify_state_bounds_with_parameters)
{
    OptimizationProblem problem;
    Parameter p1, p2, p3, p4;
    problem.minimize(x1*x2*x3).bound_state(p1,x1,p2)
                           .bound_state(x2,p3)
                           .bound_state(p4,x3);
    const size_t nb_of_states = 3;
    double x_l[nb_of_states];
    double x_u[nb_of_states];
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *p1 = a.random<double>();
        *p2 = a.random<double>();
        *p3 = a.random<double>();
        *p4 = a.random<double>();
        problem.get_state_bounds(nb_of_states, x_l, x_u);
        ASSERT_DOUBLE_EQ(*p1, x_l[0]);
        ASSERT_EQ(-INFTY, x_l[1]);
        ASSERT_EQ(*p4, x_l[2]);
        ASSERT_EQ(*p2, x_u[0]);
        ASSERT_DOUBLE_EQ(*p3, x_u[1]);
        ASSERT_EQ(INFTY, x_u[2]);
    }
}

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_constraints)
{
    OptimizationProblem hs71;
    hs71.minimize(x1*x4*(x1+x2+x3)+x3)
        .subject_to(25,x1*x2*x3*x4)
        .subject_to(40,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),40)
        .bound_state(2,x1);

    const auto constraints = hs71.get_constraints();
    ASSERT_EQ(2, constraints.size());
    const auto g1 = constraints.at(0);
    const auto g2 = constraints.at(1);
    for (size_t i = 0 ; i< 1000 ; ++i)
    {
        X1 = a.random<double>();
        X2 = a.random<double>();
        X3 = a.random<double>();
        X4 = a.random<double>();
        ASSERT_DOUBLE_EQ(X1*X2*X3*X4, g1());
        ASSERT_DOUBLE_EQ(pow(X1,2)+pow(X2,2)+pow(X3,2)+pow(X4,2), g2());
    }
}

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_gradient_of_objective_function)
{
    OptimizationProblem hs71;
    hs71.minimize(x1*x4*(x1+x2+x3)+x3)
        .subject_to(25,x1*x2*x3*x4)
        .subject_to(40,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),40)
        .bound_state(2,x1);
    const Grad grad_f = hs71.get_grad_objective_function();
    ASSERT_EQ(4, grad_f.index.size());
    ASSERT_EQ(4, grad_f.values.size());

    const auto df_dx1 = grad_f.values.at(0);
    const auto df_dx2 = grad_f.values.at(1);
    const auto df_dx3 = grad_f.values.at(2);
    const auto df_dx4 = grad_f.values.at(3);
    const double eps = 1e-6;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X1 = a.random<double>();
        X2 = a.random<double>();
        X3 = a.random<double>();
        X4 = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR(X4*(2*X1+X2+X3), df_dx1(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(X1*X4, df_dx2(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(X1*X4, df_dx3(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(X1*(X1+X2+X3), df_dx4(),eps);
    }
}

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_constraints_jacobian)
{
    OptimizationProblem hs71;
    hs71.minimize(x1*x4*(x1+x2+x3)+x3)
        .subject_to(25,x1*x2*x3*x4)
        .subject_to(40,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),40)
        .bound_state(2,x1);
    const FunctionMatrix jacobian = hs71.get_constraint_jacobian();
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
        X1 = a.random<double>();
        X2 = a.random<double>();
        X3 = a.random<double>();
        X4 = a.random<double>();
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

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_hessian)
{
    OptimizationProblem hs71;
    hs71.minimize(x1*x4*(x1+x2+x3)+x3)
        .subject_to(25,x1*x2*x3*x4)
        .subject_to(40,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),40)
        .bound_state(2,x1);
    const FunctionMatrix hessian = hs71.get_hessian();
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
    auto sigma_f = hs71.get_sigma_f();
    auto lambda = hs71.get_lambda();
    ASSERT_EQ(2, lambda.size());
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X1 = a.random<double>();
        X2 = a.random<double>();
        X3 = a.random<double>();
        X4 = a.random<double>();
        *lambda.at(0) = a.random<double>();
        *lambda.at(1) = a.random<double>();
        *sigma_f  = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR(*sigma_f*(2*X4)+2*(*lambda.at(1)), d2f_dx1dx1(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(*sigma_f*X4+(*lambda.at(0))*X3*X4, d2f_dx2dx1(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*(*lambda.at(1)), d2f_dx2dx2(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(*sigma_f*X4+(*lambda.at(0))*X2*X4, d2f_dx3dx1(),eps);
        ASSERT_SMALL_RELATIVE_ERROR((*lambda.at(0))*X1*X4, d2f_dx3dx2(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*(*lambda.at(1)), d2f_dx3dx3(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(*sigma_f*(2*X1+X2+X3)+(*lambda.at(0))*X2*X3, d2f_dx4dx1(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(*sigma_f*X1+(*lambda.at(0))*X1*X3, d2f_dx4dx2(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(*sigma_f*X1+(*lambda.at(0))*X1*X2, d2f_dx4dx3(),eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*(*lambda.at(1)), d2f_dx4dx4(),eps);
    }
}

TEST_F(OptimizationProblemTest, should_be_able_to_reset_state_bounds)
{
    OptimizationProblem problem;
    Parameter p1, p2, p3, p4;
    problem.minimize(x1*x2*x3).bound_state(p3,x1)
                           .bound_state(p1,x2,p4)
                           .bound_state(x3,p2);
    problem.reset_state_bounds();
    ASSERT_NO_THROW(problem.bound_state(p1,x1,p2));
    ASSERT_NO_THROW(problem.bound_state(x2,p3));
    ASSERT_NO_THROW(problem.bound_state(p4,x3));
    const size_t nb_of_states = 3;
    double x_l[nb_of_states];
    double x_u[nb_of_states];
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *p1 = a.random<double>();
        *p2 = a.random<double>();
        *p3 = a.random<double>();
        *p4 = a.random<double>();
        problem.get_state_bounds(nb_of_states, x_l, x_u);
        ASSERT_DOUBLE_EQ(*p1, x_l[0]);
        ASSERT_EQ(-INFTY, x_l[1]);
        ASSERT_EQ(*p4, x_l[2]);
        ASSERT_EQ(*p2, x_u[0]);
        ASSERT_DOUBLE_EQ(*p3, x_u[1]);
        ASSERT_EQ(INFTY, x_u[2]);
    }
}


TEST_F(OptimizationProblemTest, allocation_for_two_azimuths)
{
    const double theta = PI/4.;
    Parameter b1(cos(theta));
    Parameter b2(sin(theta));
    OptimizationProblem pb;
    pb.minimize(pow(x1,3)+pow(x2,3))
      .subject_to(b1,(pow(x1,2)*Cos(x3))+(pow(x2,2)*Cos(x4)),b1)
      .subject_to(b2,(pow(x1,2)*Sin(x3))+(pow(x2,2)*Sin(x4)),b2);
    auto f = (pow(x1,2)*Cos(x3))+(pow(x2,2)*Cos(x4));
    const FunctionMatrix jacobian = pb.get_constraint_jacobian();
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
        X1 = a.random<double>();
        X2 = a.random<double>();
        X3 = a.random<double>();
        X4 = a.random<double>();
        ASSERT_SMALL_RELATIVE_ERROR(2*X1*cos(X3), dg1_dx1(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*X2*cos(X4), dg1_dx2(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(-X1*X1*sin(X3), dg1_dx3(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(-X2*X2*sin(X4), dg1_dx4(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*X1*sin(X3), dg2_dx1(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(2*X2*sin(X4), dg2_dx2(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(X1*X1*cos(X3), dg2_dx3(), eps);
        ASSERT_SMALL_RELATIVE_ERROR(X2*X2*cos(X4), dg2_dx4(), eps);
    }
}
