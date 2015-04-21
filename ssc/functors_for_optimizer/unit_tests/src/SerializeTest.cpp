/*
 * SerializeTest.cpp
 *
 * \date 1 f�vr. 2013, 09:57:08
 *  \author cec
 */

#include "SerializeTest.hpp"
#include "ssc/functors_for_optimizer/Divide.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/functors_for_optimizer/Sum.hpp"
#include "ssc/functors_for_optimizer/Difference.hpp"
#include "ssc/functors_for_optimizer/Pow.hpp"
#include "ssc/functors_for_optimizer/Serialize.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"
#include "ssc/functors_for_optimizer/Ln.hpp"
#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"

using namespace ssc::functors_for_optimizer;

SerializeTest::SerializeTest() : a(ssc::random_data_generator::DataGenerator(12121)), generate(StateGenerator()), ss("")
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
    ASSERT_EQ("x / y", ss.str());
//! [SerializeTest expected output]
}

TEST_F(SerializeTest, multiply)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    Multiply d(x,y);
    Serialize v(ss);
    d.accept(v);
    ASSERT_EQ("x * y", ss.str());
}

TEST_F(SerializeTest, add)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    Sum d(x,y);
    Serialize v(ss);
    d.accept(v);
    ASSERT_EQ("x + y", ss.str());
}

TEST_F(SerializeTest, substract)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    Difference d(x,y);
    Serialize v(ss);
    d.accept(v);
    ASSERT_EQ("x - y", ss.str());
}

TEST_F(SerializeTest, power)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    Pow d(x,y);
    Serialize v(ss);
    d.accept(v);
    ASSERT_EQ("x ^ y", ss.str());
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

TEST_F(SerializeTest, DISABLED_bug_01)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    auto z = generate.state("z");
    std::stringstream ss;
    Serialize s(ss);
    (x*y/z)->diff(x)->diff(y)->diff(z)->accept(s);
    ASSERT_EQ("-1/z^2", ss.str());
}

TEST_F(SerializeTest, bug_02)
{
    auto x = generate.state("x");
    std::stringstream ss;
    Serialize s(ss);
    (2*x)->accept(s);
    ASSERT_EQ("2*x", ss.str());
}

TEST_F(SerializeTest, bug_03)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    auto z = generate.state("z");
    std::stringstream ss;
    Serialize s(ss);
    (x-z*x)->accept(s);
    ASSERT_EQ("x - z * x", ss.str());
}

TEST_F(SerializeTest, bug_04)
{
    auto x = generate.state("x");
    std::stringstream ss;
    Serialize s(ss);
    ((-1)*x)->accept(s);
    ASSERT_EQ("- x", ss.str());
}

TEST_F(SerializeTest, bug_05)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    std::stringstream ss;
    Serialize s(ss);
    (x - y)->accept(s);
    ASSERT_EQ("x - y", ss.str());
}

TEST_F(SerializeTest, bug_06)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    std::stringstream ss;
    Serialize s(ss);
    ((-1)*(x + y))->accept(s);
    ASSERT_EQ("- (x + y)", ss.str());
}

TEST_F(SerializeTest, bug_07)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    std::stringstream ss;
    Serialize s(ss);
    (x + 2*y - 3*x)->accept(s);
    ASSERT_EQ("x + 2*y - 3 * x", ss.str());
}

TEST_F(SerializeTest, bug_08)
{
    auto x = generate.state("x");
    std::stringstream ss;
    Serialize s(ss);
    pow(x-1,2)->accept(s);
    ASSERT_EQ("(x - 1) ^ 2", ss.str());
}

TEST_F(SerializeTest, bug_09)
{
    auto x = generate.state("x");
    std::stringstream ss;
    Serialize s(ss);
    (100*pow(x,2))->accept(s);
    ASSERT_EQ("100*(x ^ 2)", ss.str());
}

TEST_F(SerializeTest, bug_10)
{
    auto x = generate.state("x");
    auto y = generate.state("y");
    std::stringstream ss;
    Serialize s(ss);
    (100*pow(y-pow(x,2),2))->accept(s);
    ASSERT_EQ("100*((y - (x ^ 2)) ^ 2)", ss.str());
}

TEST_F(SerializeTest, bug_11)
{
    auto x = generate.state("x");
    std::stringstream ss;
    Serialize s(ss);
    (x-1)->accept(s);
    ASSERT_EQ("x - 1", ss.str());
}

TEST_F(SerializeTest, DISABLED_bug_12)
{
    auto x = generate.state("x");
    std::stringstream ss;
    Serialize s(ss);
    (pow((-1)*x,3))->diff(x)->accept(s);
    ASSERT_EQ("3 * (- x) ^ (3 - 1) * (- 1)", ss.str());
}

TEST_F(SerializeTest, bug_13)
{
    auto x = generate.state("x");
    std::stringstream ss;
    Serialize s(ss);
    (2*(x-1))->accept(s);
    ASSERT_EQ("2*(x - 1)", ss.str());
}
