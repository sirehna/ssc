/*
 * IpoptSolverTest.cpp
 *
 * \date 22 févr. 2013, 15:28:17
 * \author cec
 */

#include "IpoptSolverTest.hpp"
#include "ssc/ipopt_interface/IpoptSolver.hpp"
#include "ssc/ipopt_interface/IpoptSolverException.hpp"
#include "ssc/optimizer/OptimizationProblem.hpp"
#include "ssc/optimizer/OptimizationResult.hpp"

#include "ssc/functors_for_optimizer/State.hpp"

#include "ssc/macros/extra_test_assertions.hpp"

#include "ssc/functors_for_optimizer/Cos.hpp"
#include "ssc/functors_for_optimizer/Sin.hpp"
#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"

#include <iostream>
#include <cmath>

#define PI (4.*atan(1.))

using namespace ssc::ipopt_interface;
using namespace ssc::functors_for_optimizer;
using namespace ssc::optimizer;

IpoptSolverTest::IpoptSolverTest() : a(ssc::random_data_generator::DataGenerator(56)),
                                     generate(StateGenerator()),
                                     x1(generate.state("x1")),
                                     x2(generate.state("x2")),
                                     x3(generate.state("x3")),
                                     x4(generate.state("x4"))
{
}

IpoptSolverTest::~IpoptSolverTest()
{
}

void IpoptSolverTest::SetUp()
{
}

void IpoptSolverTest::TearDown()
{
}

TEST_F(IpoptSolverTest, example)
{
//! [IpoptSolverTest example]
    TR1(shared_ptr)<OptimizationProblem> hs71(new OptimizationProblem());
    hs71->minimize(x1*x4*(x1+x2+x3)+x3)
        .subject_to(25,x1*x2*x3*x4)
        .subject_to(40,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),40)
        .bound_state(1,x1,5)
        .bound_state(1,x2,5)
        .bound_state(1,x3,5)
        .bound_state(1,x4,5);
    IpoptParameters ipopt_parameters;
    ipopt_parameters.print_level = 5;
    IpoptSolver optimize(hs71,ipopt_parameters);
    std::vector<double> x0(4,0);
    x0[0] = 1;
    x0[1] = 5;
    x0[2] = 5;
    x0[3] = 1;
    auto result = optimize.solve(x0);
//! [IpoptSolverTest example]
//! [IpoptSolverTest expected output]
    const double eps = 1e-6;

    ASSERT_EQ(4, result.state_values.size());
    ASSERT_SMALL_RELATIVE_ERROR(1.,result.state_values["x1"],eps);
    ASSERT_SMALL_RELATIVE_ERROR(4.74299963,result.state_values["x2"],eps);
    ASSERT_SMALL_RELATIVE_ERROR(3.82114998,result.state_values["x3"],eps);
    ASSERT_SMALL_RELATIVE_ERROR(1.37940829,result.state_values["x4"],eps);
//! [IpoptSolverTest expected output]
}

TEST_F(IpoptSolverTest, rosenbrock_banana)
{
    TR1(shared_ptr)<OptimizationProblem> rosenbrock(new OptimizationProblem());
    rosenbrock->minimize(100*pow(x2-pow(x1,2),2)+pow(x1-1,2));
    IpoptParameters ipopt_parameters;
    ipopt_parameters.print_level = 5;
    IpoptSolver optimize(rosenbrock, ipopt_parameters);
    std::vector<double> x0(2,0);
    x0[0] = 5;
    x0[1] = 3;
    auto result = optimize.solve(x0);
    ASSERT_EQ(2, result.state_values.size());
    const double eps = 1e-6;
    ASSERT_SMALL_RELATIVE_ERROR(1.,result.state_values["x1"],eps);
    ASSERT_SMALL_RELATIVE_ERROR(1.,result.state_values["x2"],eps);
}

TEST_F(IpoptSolverTest, test_01)
{
    TR1(shared_ptr)<OptimizationProblem> pb(new OptimizationProblem());
    Parameter c0(2);
    pb->minimize(pow(x1*x1-c0,2));
    IpoptSolver optimize(pb);
    const std::vector<double> x0(1,1);
    const double eps = 1e-3;
    c0 = 2;
    auto result = optimize.solve(x0);
    ASSERT_SMALL_RELATIVE_ERROR(sqrt(2.),result.state_values["x1"],eps);
}

TEST_F(IpoptSolverTest, test_02)
{
    TR1(shared_ptr)<OptimizationProblem> pb(new OptimizationProblem());
    Parameter c0(2);
    pb->minimize(pow(x1*x1-c0,2));
    IpoptSolver optimize(pb);
    const std::vector<double> x0(1,1);
    const double eps = 1e-3;
    for (size_t i = 0 ; i < 20 ; ++i)
    {
        c0 = a.random<double>().between(0,100);
        auto result = optimize.solve(x0);
        ASSERT_SMALL_RELATIVE_ERROR(sqrt(c0.get_lambda()()),result.state_values["x1"],eps);
    }
}

TEST_F(IpoptSolverTest, DISABLED_old_maroff_allocation_problem_does_not_converge)
{
    // Constraints are non-convex!
    const double theta = PI/4.;
    Parameter b1(cos(theta));
    Parameter b2(sin(theta));
    TR1(shared_ptr)<OptimizationProblem> pb(new OptimizationProblem());
    pb->minimize(pow(x1,3)+pow(x2,3))
       .subject_to(b1,(pow(x1,2)*Cos(x3))+(pow(x2,2)*Cos(x4)),b1)
       .subject_to(b2,(pow(x1,2)*Sin(x3))+(pow(x2,2)*Sin(x4)),b2)
       .bound_state(0,x1,1)
       .bound_state(0,x2,1)
       .bound_state(0,x3,PI)
       .bound_state(0,x4,PI);
    IpoptSolver optimize(pb);
    std::vector<double> x0(4,0);
    x0[0] = 0.5;
    x0[1] = 0.5;
    x0[2] = PI/2;
    x0[3] = PI/2;
    const double eps = 1e-3;

    const auto result = optimize.solve(x0);

    const bool converged = (fabs(cos(theta)-result.constraint_values.at(0)) < eps)
                       and (fabs(sin(theta)-result.constraint_values.at(1)) < eps);

    ASSERT_FALSE(converged);
}

TEST_F(IpoptSolverTest, new_allocation_problem_converges)
{
    const double theta = PI/4.;
    Parameter b1(cos(theta));
    Parameter b2(sin(theta));
    TR1(shared_ptr)<OptimizationProblem> pb(new OptimizationProblem());
    const double p = 1000; // Penalty factor
    pb->minimize((pow(x1,3)+pow(x2,3))/2
                +p*pow((pow(x1,2)*Cos(x3))+(pow(x2,2)*Cos(x4))-b1,2)/2
                +p*pow((pow(x1,2)*Sin(x3))+(pow(x2,2)*Sin(x4))-b2,2)/2)
       .bound_state(0,x1,1)
       .bound_state(0,x2,1)
       .bound_state(0,x3,PI)
       .bound_state(0,x4,PI);
    IpoptSolver optimize(pb);
    std::vector<double> x0(4,0);
    x0[0] = 0.5;
    x0[1] = 0.5;
    x0[2] = PI/2;
    x0[3] = PI/2;
    const double eps = 1e-3;
    auto result = optimize.solve(x0);

    const double x1_ = result.state_values["x1"];
    const double x2_ = result.state_values["x2"];
    const double x3_ = result.state_values["x3"];
    const double x4_ = result.state_values["x4"];

    ASSERT_SMALL_RELATIVE_ERROR(cos(theta),x1_*x1_*cos(x3_)+x2_*x2_*cos(x4_),eps);
    ASSERT_SMALL_RELATIVE_ERROR(sin(theta),x1_*x1_*sin(x3_)+x2_*x2_*sin(x4_),eps);
}

TEST_F(IpoptSolverTest, can_solve_a_maximization_problem)
{
    TR1(shared_ptr)<OptimizationProblem> pb(new OptimizationProblem());
    pb->maximize(143*x1+60*x2)
      .subject_to(120*x1 + 210*x2, 15000)
      .subject_to(110*x1 + 30*x2, 4000)
      .subject_to(x1 + x2, 75 )
      .bound_state(0,x1)
      .bound_state(0,x2);
    IpoptSolver optimize(pb);
    const std::vector<double> x0(2,0);
    auto res = optimize.solve(x0);
    ASSERT_DOUBLE_EQ(6315.625, res.value_of_the_objective_function);
    ASSERT_EQ(2, res.state_values.size());
    ASSERT_DOUBLE_EQ(21.875, res.state_values["x1"]);
    ASSERT_DOUBLE_EQ(53.125, res.state_values["x2"]);
}

TEST_F(IpoptSolverTest, cannot_use_ipopt_when_there_are_binary_variables)
{
    TR1(shared_ptr)<OptimizationProblem> pb(new OptimizationProblem());
    pb->maximize(143*x1+60*x2)
      .subject_to(120*x1 + 210*x2, 15000)
      .subject_to(110*x1 + 30*x2, 4000)
      .subject_to(x1 + x2, 75 )
      .binary(x1);
    ASSERT_THROW(IpoptSolver s(pb), IpoptSolverException);
}

TEST_F(IpoptSolverTest, cannot_use_ipopt_when_there_are_integer_variables)
{
    TR1(shared_ptr)<OptimizationProblem> pb(new OptimizationProblem());
    pb->maximize(143*x1+60*x2)
      .subject_to(120*x1 + 210*x2, 15000)
      .subject_to(110*x1 + 30*x2, 4000)
      .subject_to(x1 + x2, 75 )
      .integer(x2);
    ASSERT_THROW(IpoptSolver s(pb), IpoptSolverException);
}
