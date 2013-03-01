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
    OptimizationProblem hs71;
    hs71.minimize(x1*x4*(x1+x2+x3)+x3)
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
    const auto result = optimize.solve(x0);
//! [IpoptSolverTest example]
//! [IpoptSolverTest expected output]
    const double eps = 1e-6;
    for (auto state = result.state_values.begin() ; state != result.state_values.end() ; ++state)
    {
        COUT(*state);
    }

    ASSERT_EQ(4, result.state_values.size());
    ASSERT_SMALL_RELATIVE_ERROR(1,result.state_values.at(0),eps);
    ASSERT_SMALL_RELATIVE_ERROR(4.74299963,result.state_values.at(1),eps);
    ASSERT_SMALL_RELATIVE_ERROR(3.82114998,result.state_values.at(2),eps);
    ASSERT_SMALL_RELATIVE_ERROR(1.37940829,result.state_values.at(3),eps);
//! [IpoptSolverTest expected output]
}

TEST_F(IpoptSolverTest, rosenbrock_banana)
{
    OptimizationProblem rosenbrock;
    rosenbrock.minimize(100*pow(x2-pow(x1,2),2)+pow(x1-1,2));
    IpoptParameters ipopt_parameters;
    ipopt_parameters.print_level = 5;
    IpoptSolver optimize(rosenbrock, ipopt_parameters);

    const auto result = optimize.solve({5,3});
    ASSERT_EQ(2, result.state_values.size());
    const double eps = 1e-6;
    ASSERT_SMALL_RELATIVE_ERROR(1,result.state_values.at(0),eps);
    ASSERT_SMALL_RELATIVE_ERROR(1,result.state_values.at(1),eps);
}

TEST_F(IpoptSolverTest, test_01)
{
    OptimizationProblem pb;
    Parameter c0(2);
    pb.minimize(pow(x1*x1-c0,2));
    IpoptSolver optimize(pb);
    const std::vector<double> x0({1});
    const double eps = 1e-3;
    *c0 = 2;
    const auto result = optimize.solve(x0);
    ASSERT_SMALL_RELATIVE_ERROR(sqrt(2),result.state_values.at(0),eps);
}

TEST_F(IpoptSolverTest, test_02)
{
    OptimizationProblem pb;
    Parameter c0(2);
    pb.minimize(pow(x1*x1-c0,2));
    IpoptSolver optimize(pb);
    const std::vector<double> x0({1});
    const double eps = 1e-3;
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        *c0 = a.random<double>().between(0,100);
        const auto result = optimize.solve(x0);
        ASSERT_SMALL_RELATIVE_ERROR(sqrt(*c0),result.state_values.at(0),eps);
    }
}

