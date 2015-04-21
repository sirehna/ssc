/*
 * SerializeReversePolishTest.cpp
 *
 * \date 28 f�vr. 2013, 17:02:40
 *  \author cec
 */

#include "SerializeReversePolishTest.hpp"
#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"
#include "ssc/functors_for_optimizer/SerializeReversePolish.hpp"
#include "ssc/functors_for_optimizer/Sum.hpp"
#include "ssc/functors_for_optimizer/Pow.hpp"
#include "ssc/functors_for_optimizer/Divide.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"

using namespace ssc::functors_for_optimizer;

SerializeReversePolishTest::SerializeReversePolishTest() : a(ssc::random_data_generator::DataGenerator(336699)),
generate(StateGenerator()),
x(generate.state("x")),
y(generate.state("y")),
ss(""),
serialize(SerializeReversePolish(ss))
{
}

SerializeReversePolishTest::~SerializeReversePolishTest()
{
}

void SerializeReversePolishTest::SetUp()
{
}

void SerializeReversePolishTest::TearDown()
{
}

TEST_F(SerializeReversePolishTest, example)
{
//! [SerializeReversePolishTest example]
    (pow((2*x+y)->clone(),y-4)/(x-y))->accept(serialize);

//! [SerializeReversePolishTest example]
//! [SerializeReversePolishTest expected output]
    ASSERT_EQ("Divide(Pow(Sum(2*x,y),Sum(y,-4)),Sum(x,-y))", ss.str());
//! [SerializeReversePolishTest expected output]
}

TEST_F(SerializeReversePolishTest, bug_01)
{
    auto F = x;
    F->multiply_by(-2);
    F->accept(serialize);
    ASSERT_EQ("-2*x", ss.str());
}

TEST_F(SerializeReversePolishTest, bug_02)
{
    pow(y-pow(x,2),2)->diff(x)->accept(serialize);
    ASSERT_EQ("Multiply(2*Sum(y,-Pow(x,2)),Sum(-Multiply(2*x)))", ss.str());
}
