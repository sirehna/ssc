/*
 * LPSolverTests.cpp
 *
 * \date 20 nov. 2013, 14:02:04
 *  \author cec
 */

#include "LPSolverTests.hpp"
#include "LPSolver.hpp"
#include "StateGenerator.hpp"
#include "OptimizationProblem.hpp"

#include "test_macros.hpp"

LPSolverTests::LPSolverTests() : a(DataGenerator(166799))
{
}

LPSolverTests::~LPSolverTests()
{
}

void LPSolverTests::SetUp()
{
}

void LPSolverTests::TearDown()
{
}

TEST_F(LPSolverTests, example)
{
//! [LPSolverTests example]
    StateGenerator generate;
    auto x = generate.state("x");
    auto y = generate.state("y");
    std::shared_ptr<OptimizationProblem> pb(new OptimizationProblem());
    pb->minimize((-1)*(143*x+60*y))
      .subject_to(120*x + 210*y, 15000)
      .subject_to(110*x + 30*y, 4000)
      .subject_to(x + y, 75 )
      .bound_state(0,x)
      .bound_state(0,y);
    std::cout << *pb << std::endl;
//! [LPSolverTests example]
//! [LPSolverTests expected output]
    LPSolver solver(pb);

    auto res = solver.solve();
/*
    ASSERT_DOUBLE_EQ(6315.625, res.value_of_the_objective_function);
    ASSERT_EQ(2, res.state_values.size());
    ASSERT_DOUBLE_EQ(21.875, res.state_values["x"]);
    ASSERT_DOUBLE_EQ(53.125, res.state_values["y"]);*/
//! [LPSolverTests expected output]
}



