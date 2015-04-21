/*
 * StateGetterTest.cpp
 *
 * \date 20 f�vr. 2013, 12:44:42
 *  \author cec
 */

#include "StateGetterTest.hpp"
#include "StateGetter.hpp"
#include "FunctorAlgebra.hpp"
#include "StateGenerator.hpp"
#include "Multiply.hpp"
#include "Sum.hpp"


StateGetterTest::StateGetterTest() : a(ssc::random_data_generator::DataGenerator(1))
{
}

StateGetterTest::~StateGetterTest()
{
}

void StateGetterTest::SetUp()
{
}

void StateGetterTest::TearDown()
{
}

TEST_F(StateGetterTest, example)
{
//! [StateGetterTest example]
    StateGenerator generate;
    auto x = generate.state("x");
    auto y = generate.state("y");
    auto z = generate.state("z");
    auto t = generate.state("t");
    auto f = x*t+y;
    auto g = z*z*z;
    StateGetter get_states;
//! [StateGetterTest example]
//! [StateGetterTest expected output]
    get_states(f);
    auto f_states = get_states.get();
    get_states(g);
    auto f_and_g_states = get_states.get();
    ASSERT_EQ(3,f_states.size());
    ASSERT_EQ(4,f_and_g_states.size());
    ASSERT_EQ(*x,*f_states.at(0));
    ASSERT_EQ(*y,*f_states.at(1));
    ASSERT_EQ(*t,*f_states.at(2));
    ASSERT_EQ(*x,*f_and_g_states.at(0));
    ASSERT_EQ(*y,*f_and_g_states.at(1));
    ASSERT_EQ(*z,*f_and_g_states.at(2));
    ASSERT_EQ(*t,*f_and_g_states.at(3));
//! [StateGetterTest expected output]
}

TEST_F(StateGetterTest, should_work_with_vectors_of_functions)
{
    StateGenerator generate;
    auto x1 = generate.state("x1");
    auto x2 = generate.state("x2");
    auto x3 = generate.state("x3");
    auto x4 = generate.state("x4");
    auto x5 = generate.state("x5");
    auto x6 = generate.state("x6");
    auto x7 = generate.state("x7");
    auto x8 = generate.state("x8");
    auto f = x1*x2+x4;
    std::vector<NodePtr> g;
    g.push_back(x2*x3);
    g.push_back(x3*x4);
    g.push_back(x4*x5);
    g.push_back(x5*x6);
    g.push_back(x6*x7);
    g.push_back(x7*x8);
    StateGetter get_states;
    get_states(f);
    get_states(g);
    auto states = get_states.get();
    ASSERT_EQ(8,states.size());
    ASSERT_EQ(*x1,*states.at(0));
    ASSERT_EQ(*x2,*states.at(1));
    ASSERT_EQ(*x3,*states.at(2));
    ASSERT_EQ(*x4,*states.at(3));
    ASSERT_EQ(*x5,*states.at(4));
    ASSERT_EQ(*x6,*states.at(5));
    ASSERT_EQ(*x7,*states.at(6));
    ASSERT_EQ(*x8,*states.at(7));
}

