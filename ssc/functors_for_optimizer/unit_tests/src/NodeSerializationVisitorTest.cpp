/*
 * NodeSerializationVisitorTest.cpp
 *
 * \date 28 janv. 2013, 12:22:30
 *  \author cec
 */

#include "NodeSerializationVisitorTest.hpp"
#include "NodeSerializationVisitor.hpp"
#include "StateGenerator.hpp"
#include "Multiply.hpp"

NodeSerializationVisitorTest::NodeSerializationVisitorTest() : a(DataGenerator(1)),
generate(StateGenerator())
{
}

NodeSerializationVisitorTest::~NodeSerializationVisitorTest()
{
}

void NodeSerializationVisitorTest::SetUp()
{
}

void NodeSerializationVisitorTest::TearDown()
{
}

TEST_F(NodeSerializationVisitorTest, example)
{
//! [NodeSerializationVisitorTest example]
    const std::string state_name = a.random<std::string>();
    const State x = generate.state(state_name);
    std::stringstream ss;
    NodeSerializationVisitor v(ss);

//! [NodeSerializationVisitorTest example]
//! [NodeSerializationVisitorTest expected output]
    x.accept(v);
    ASSERT_EQ(state_name, ss.str());
//! [NodeSerializationVisitorTest expected output]
}

TEST_F(NodeSerializationVisitorTest, serialize_product)
{
    const State x = generate.state("x");
    std::stringstream ss;
    NodeSerializationVisitor v(ss);
    Multiply(x,x).accept(v);
    ASSERT_EQ("(x)*(x)", ss.str());
}

