/*
 * IpoptSolverTest.cpp
 *
 * \date 22 févr. 2013, 15:28:17
 *  \author cec
 */

#include "IpoptSolverTest.hpp"
#include "IpoptSolver.hpp"
#include "OptimizationProblem.hpp"
#include "StateGenerator.hpp"
#include "test_macros.hpp"
#include "OptimizationResult.hpp"

IpoptSolverTest::IpoptSolverTest() : a(DataGenerator(56))
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
    StateGenerator generate;
    auto x1 = generate.state("x1");
    auto x2 = generate.state("x2");
    auto x3 = generate.state("x3");
    auto x4 = generate.state("x4");
    OptimizationProblem hs71;
    hs71.minimize(x1*x4*(x1+x2+x3)+x3)
        .subject_to(25,x1*x2*x3*x4)
        .subject_to(40,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),40)
        .bound_state(1,x1,5)
        .bound_state(1,x2,5)
        .bound_state(1,x3,5)
        .bound_state(1,x4,5);
    IpoptSolver optimize(hs71);
    const std::vector<double> x0({1,5,5,1});
    auto result = optimize.solve(x0);
//! [IpoptSolverTest example]
//! [IpoptSolverTest expected output]
    ASSERT_DOUBLE_EQ(1,result.state_values.at(0));
//! [IpoptSolverTest expected output]
}



