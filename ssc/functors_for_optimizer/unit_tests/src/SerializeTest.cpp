/*
 * SerializeTest.cpp
 *
 * \date 1 févr. 2013, 09:57:08
 *  \author cec
 */

#include "SerializeTest.hpp"
#include "Divide.hpp"
#include "Multiply.hpp"
#include "Sum.hpp"
#include "Difference.hpp"
#include "Pow.hpp"
#include "Serialize.hpp"
#include "StateGenerator.hpp"
#include "Ln.hpp"

SerializeTest::SerializeTest() : a(DataGenerator(12121)), generate(StateGenerator()), ss("")
{
}

SerializeTest::~SerializeTest()
{
}

void SerializeTest::SetUp()
{
}

void SerializeTest::TearDown()
{
}

TEST_F(SerializeTest, example)
{
//! [SerializeTest example]
    auto x = generate.state("x");
    auto y = generate.state("y");
    Divide d(x,y);
    Serialize v(ss);
    d.accept(v);
//! [SerializeTest example]
//! [SerializeTest expected output]
    ASSERT_EQ("(x / y)", ss.str());
//! [SerializeTest expected output]
}

TEST_F(SerializeTest, multiply)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    Multiply d(x,y);
    Serialize v(ss);
    d.accept(v);
    ASSERT_EQ("(x * y)", ss.str());
}

TEST_F(SerializeTest, add)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    Sum d(x,y);
    Serialize v(ss);
    d.accept(v);
    ASSERT_EQ("(x + y)", ss.str());
}

TEST_F(SerializeTest, substract)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    Difference d(x,y);
    Serialize v(ss);
    d.accept(v);
    ASSERT_EQ("(x - y)", ss.str());
}

TEST_F(SerializeTest, power)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    Pow d(x,y);
    Serialize v(ss);
    d.accept(v);
    ASSERT_EQ("(x ^ y)", ss.str());
}

TEST_F(SerializeTest, state)
{
    const std::string state_name = a.random<std::string>();
    auto x = generate.state(state_name);
    Serialize v(ss);
    x->accept(v);
    ASSERT_EQ(state_name, ss.str());
}

TEST_F(SerializeTest, constant)
{
    const double cst = 12365;
    Parameter c(cst);
    Serialize v(ss);
    c.accept(v);
    ASSERT_EQ("12365", ss.str());
}

TEST_F(SerializeTest, logarithm)
{
    const auto x = generate.state("x");
    Ln l(x);
    Serialize v(ss);
    l.accept(v);
    ASSERT_EQ("log(x)", ss.str());
}
