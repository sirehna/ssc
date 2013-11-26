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
<<<<<<< HEAD
    std::tr1::shared_ptr<OptimizationProblem> pb(new OptimizationProblem());
    pb->maximize(143*x+60*y)
=======
    std::shared_ptr<OptimizationProblem> pb(new OptimizationProblem());
    pb->minimize((-1)*(143*x+60*y))
>>>>>>> Stubbed lpsolve_interface
      .subject_to(120*x + 210*y, 15000)
      .subject_to(110*x + 30*y, 4000)
      .subject_to(x + y, 75 )
      .bound_state(0,x)
      .bound_state(0,y);
<<<<<<< HEAD
=======
    std::cout << *pb << std::endl;
>>>>>>> Stubbed lpsolve_interface
//! [LPSolverTests example]
//! [LPSolverTests expected output]
    LPSolver solver(pb);

<<<<<<< HEAD
    auto res = solver.solve({0,0});

    ASSERT_DOUBLE_EQ(6315.625, res.value_of_the_objective_function);
    ASSERT_EQ(2, res.state_values.size());
    ASSERT_DOUBLE_EQ(21.875, res.state_values["x"]);
    ASSERT_DOUBLE_EQ(53.125, res.state_values["y"]);
//! [LPSolverTests expected output]
}

TEST_F(LPSolverTests, can_use_lp_solve_on_non_linear_cost)
{
    // We don't use the objective function directly: we only use its gradient so
    // linearizing around (1,1) should give the same result as before
    StateGenerator generate;
    auto x = generate.state("x");
    auto y = generate.state("y");
    std::tr1::shared_ptr<OptimizationProblem> pb(new OptimizationProblem());
    pb->maximize(71.5*x*x+30*y*y)
      .subject_to(120*x + 210*y, 15000)
      .subject_to(110*x + 30*y, 4000)
      .subject_to(x + y, 75 )
      .bound_state(0,x)
      .bound_state(0,y);
    LPSolver solver(pb);

    auto res = solver.solve({1,1});
    ASSERT_DOUBLE_EQ(6315.625, res.value_of_the_objective_function);
}

TEST_F(LPSolverTests, can_solve_binary_problems)
{
    StateGenerator generate;
    auto x = generate.state("x");
    auto y = generate.state("y");
    std::tr1::shared_ptr<OptimizationProblem> pb(new OptimizationProblem());
    pb->maximize(x-y)
      .binary(x)
      .binary(y);
    LPSolver solver(pb);
    auto res = solver.solve(a.random_vector_of<double>().of_size(2));
    ASSERT_EQ(1,res.state_values["x"]);
    ASSERT_EQ(0,res.state_values["y"]);
}
=======
    auto res = solver.solve();
/*
    ASSERT_DOUBLE_EQ(6315.625, res.value_of_the_objective_function);
    ASSERT_EQ(2, res.state_values.size());
    ASSERT_DOUBLE_EQ(21.875, res.state_values["x"]);
    ASSERT_DOUBLE_EQ(53.125, res.state_values["y"]);*/
//! [LPSolverTests expected output]
}



>>>>>>> Stubbed lpsolve_interface
