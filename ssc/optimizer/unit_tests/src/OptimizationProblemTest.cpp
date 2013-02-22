/*
 * OptimizationProblemTest.cpp
 *
 * \date 21 févr. 2013, 10:15:03
 *  \author cec
 */

#include "OptimizationProblemTest.hpp"
#include "StateGenerator.hpp"
#include "OptimizationProblem.hpp"
#include "test_macros.hpp"

OptimizationProblemTest::OptimizationProblemTest() : a(DataGenerator(1))
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
    StateGenerator generate;
    auto x1 = generate.state("x1");
    auto x2 = generate.state("x2");
    auto x3 = generate.state("x3");
    auto x4 = generate.state("x4");

    OptimizationProblem hs71;
//! [OptimizationProblemTest example]
//! [OptimizationProblemTest expected output]
    /*hs71.minimize(x1*x4*(x1+x2+x3)+x3)
        .subject_to(25,LESS_THAN,x1*x2*x3*x4)
        .subject_to(pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),EQUALS,40);*/
//! [OptimizationProblemTest expected output]
}

TEST_F(OptimizationProblemTest,

