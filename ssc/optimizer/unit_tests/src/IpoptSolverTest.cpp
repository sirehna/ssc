/*
 * IpoptSolverTest.cpp
 *
 * \date 22 févr. 2013, 15:28:17
 *  \author cec
 */

#include "IpoptSolverTest.hpp"
#include "IpoptSolver.hpp"
#include "OptimizationProblem.hpp"
#include "OptimizationResult.hpp"

#include "State.hpp"

#include "extra_test_assertions.hpp"

#include "Cos.hpp"
#include "Sin.hpp"
#include "FunctorAlgebra.hpp"

#include <iostream>
#include <cmath>
#define PI (4.*atan(1.))
IpoptSolverTest::IpoptSolverTest() : a(DataGenerator(56)),
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
    std::tr1::shared_ptr<OptimizationProblem> hs71(new OptimizationProblem());
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
    const std::vector<double> x0({1,5,5,1});
    auto result = optimize.solve(x0);
//! [IpoptSolverTest example]
//! [IpoptSolverTest expected output]
    const double eps = 1e-6;

    ASSERT_EQ(4, result.state_values.size());
    ASSERT_SMALL_RELATIVE_ERROR(1,result.state_values["x1"],eps);
    ASSERT_SMALL_RELATIVE_ERROR(4.74299963,result.state_values["x2"],eps);
    ASSERT_SMALL_RELATIVE_ERROR(3.82114998,result.state_values["x3"],eps);
    ASSERT_SMALL_RELATIVE_ERROR(1.37940829,result.state_values["x4"],eps);
//! [IpoptSolverTest expected output]
}

TEST_F(IpoptSolverTest, rosenbrock_banana)
{
    std::tr1::shared_ptr<OptimizationProblem> rosenbrock(new OptimizationProblem());
    rosenbrock->minimize(100*pow(x2-pow(x1,2),2)+pow(x1-1,2));
    IpoptParameters ipopt_parameters;
    ipopt_parameters.print_level = 5;
    IpoptSolver optimize(rosenbrock, ipopt_parameters);

    auto result = optimize.solve({5,3});
    ASSERT_EQ(2, result.state_values.size());
    const double eps = 1e-6;
    ASSERT_SMALL_RELATIVE_ERROR(1,result.state_values["x1"],eps);
    ASSERT_SMALL_RELATIVE_ERROR(1,result.state_values["x2"],eps);
}

TEST_F(IpoptSolverTest, test_01)
{
    std::tr1::shared_ptr<OptimizationProblem> pb(new OptimizationProblem());
    Parameter c0(2);
    pb->minimize(pow(x1*x1-c0,2));
    IpoptSolver optimize(pb);
    const std::vector<double> x0({1});
    const double eps = 1e-3;
    c0 = 2;
    auto result = optimize.solve(x0);
    ASSERT_SMALL_RELATIVE_ERROR(sqrt(2),result.state_values["x1"],eps);
}

TEST_F(IpoptSolverTest, test_02)
{
    std::tr1::shared_ptr<OptimizationProblem> pb(new OptimizationProblem());
    Parameter c0(2);
    pb->minimize(pow(x1*x1-c0,2));
    IpoptSolver optimize(pb);
    const std::vector<double> x0({1});
    const double eps = 1e-3;
    for (size_t i = 0 ; i < 20 ; ++i)
    {
        c0 = a.random<double>().between(0,100);
        auto result = optimize.solve(x0);
        ASSERT_SMALL_RELATIVE_ERROR(sqrt(c0.get_lambda()()),result.state_values["x1"],eps);
    }
}

TEST_F(IpoptSolverTest, DISABLED_allocation_problem)
{
    const double theta = PI/4.;
    Parameter b1(cos(theta));
    Parameter b2(sin(theta));
    std::tr1::shared_ptr<OptimizationProblem> pb(new OptimizationProblem());
    pb->minimize(pow(x1,3)+pow(x2,3))
       .subject_to(b1,(pow(x1,2)*Cos(x3))+(pow(x2,2)*Cos(x4)),b1)
       .subject_to(b2,(pow(x1,2)*Sin(x3))+(pow(x2,2)*Sin(x4)),b2)
       .bound_state(0,x1,1)
       .bound_state(0,x2,1)
       .bound_state(0,x3,PI)
       .bound_state(0,x4,PI);
    IpoptSolver optimize(pb);
    const std::vector<double> x0({0.5,0.5,PI/2,PI/2});
    const double eps = 1e-3;

    const auto result = optimize.solve(x0);

    ASSERT_SMALL_RELATIVE_ERROR(cos(theta),result.constraint_values.at(0),eps);
    ASSERT_SMALL_RELATIVE_ERROR(sin(theta),result.constraint_values.at(1),eps);
}

