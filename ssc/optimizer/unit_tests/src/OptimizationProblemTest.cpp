/*
 * OptimizationProblemTest.cpp
 *
 * \date 21 févr. 2013, 10:15:03
 *  \author cec
 */

#include "OptimizationProblemTest.hpp"
#include "OptimizationProblem.hpp"
#include "GradHes.hpp"

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
    const auto F = hs71.get_objective_function();
    const auto objective_function = F->get_lambda();
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
    double gl[2];
    double gu[2];
    OptimizationProblem hs71;
    hs71.minimize(x1*x4*(x1+x2+x3)+x3)
        .subject_to(25,x1*x2*x3*x4)
        .subject_to(40,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),40);
    hs71.get_constraint_bounds(gl, gu);
    ASSERT_EQ(25, gl[0]);
    ASSERT_EQ(40, gl[1]);
    ASSERT_EQ(2e19, gu[0]);
    ASSERT_EQ(40, gu[1]);
}

TEST_F(OptimizationProblemTest, method_to_retrieve_constraint_bounds_should_throw_if_any_pointers_are_null)
{
    double gl[2];
    double gu[2];
    OptimizationProblem pb;
    ASSERT_THROW(pb.get_constraint_bounds(NULL, gu), OptimizationProblemException);
    ASSERT_THROW(pb.get_constraint_bounds(gl, NULL), OptimizationProblemException);
    ASSERT_THROW(pb.get_constraint_bounds(NULL, NULL), OptimizationProblemException);
}

/*
TEST_F(OptimizationProblemTest, should_be_able_to_set_and_retrieve_state_bounds)
{

}



TEST_F(OptimizationProblemTest, different_ways_to_specify_constraint_bounds)
{
    OptimizationProblem problem;
    problem.minimize(x1*x4)
           .subject_to(25,x1*x3)
           .subject_to(40,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),40)
           .subject_to(x1*x3,50);
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
*/
