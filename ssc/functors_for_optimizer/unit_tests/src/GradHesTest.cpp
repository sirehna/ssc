/*
 * GradHesTest.cpp
 *
 * \date 20 févr. 2013, 11:46:48
 *  \author cec
 */

#include "GradHesTest.hpp"
#include "GradHes.hpp"
#include "FunctorAlgebra.hpp"
#include "StateGenerator.hpp"
#include "Sum.hpp"
#include "Multiply.hpp"
#include "Pow.hpp"
#include "Serialize.hpp"

GradHesTest::GradHesTest() : a(DataGenerator(76945))
{
}

GradHesTest::~GradHesTest()
{
}

void GradHesTest::SetUp()
{
}

void GradHesTest::TearDown()
{
}

TEST_F(GradHesTest, example)
{
//! [GradHesTest example]
    StateGenerator generate;
    auto x1 = generate.state("x1");
    auto x2 = generate.state("x2");
    auto x3 = generate.state("x3");
    auto x4 = generate.state("x4");
    auto f = x1*x4*(x1+x2+x3)+x3;
    std::vector<NodePtr> g;
    g.push_back(x1*x2*x3*x4);
    g.push_back(pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2));
    /*
    const StateList states = get_states(f,g);
    states.push_back(x1);
    states.push_back(x2);
    states.push_back(x3);
    states.push_back(x4);
    Grad grad_f = grad(f, states);
    Parameter sigma_f(1), lambda_1(1), lambda_2(1);
    std::vector<Parameter> lambda;
    lambda.push_back(lambda_1);
    lambda.push_back(lambda_2);
    Hes hessian = hes(f,g,sigma_f,lambda);
//! [GradHesTest example]
//! [GradHesTest expected output]
    ASSERT_EQ(4, grad_f.size());
    ASSERT_EQ(10, hessian.size());
//! [GradHesTest expected output]
 * */
}

TEST_F(GradHesTest, should_be_able_to_retrieve_states_from_objective_and_constraints)
{
    StateGenerator generate;
    auto x1 = generate.state("x1");
    auto x2 = generate.state("x2");
    auto x3 = generate.state("x3");
    auto x4 = generate.state("x4");
    auto f = x1*x4*(x1+x2+x3)+x3;
    std::vector<NodePtr> g;
    g.push_back(x1*x2*x3*x4);
    g.push_back(pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2));
    const StateList states = get_states(f,g);

    ASSERT_EQ(4, states.size());
    ASSERT_EQ(*x1, *states.at(0));
    ASSERT_EQ(*x2, *states.at(1));
    ASSERT_EQ(*x3, *states.at(2));
    ASSERT_EQ(*x4, *states.at(3));
}

