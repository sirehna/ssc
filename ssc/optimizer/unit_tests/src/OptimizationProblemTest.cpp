/*
 * OptimizationProblemTest.cpp
 *
 * \date 21 févr. 2013, 10:15:03
 *  \author cec
 */

#include "OptimizationProblemTest.hpp"
#include "OptimizationProblem.hpp"
#include "GradHes.hpp"

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

}

TEST_F(OptimizationProblemTest, different_ways_to_specify_constraint_bounds)
{

}

TEST_F(OptimizationProblemTest, should_be_able_to_specify_constraints_bounds_with_parameters)
{

}


TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_constraints)
{

}

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_gradient_of_objective_function)
{

}

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_constraints_jacobian)
{

}

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_hessian)
{

}

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_sigmaf_and_lambda_corresponding_to_hessian)
{

}
