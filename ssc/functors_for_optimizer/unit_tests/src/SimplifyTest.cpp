/*
 * SimplifyTest.cpp
 *
 * \date 13 f�vr. 2013, 08:57:25
 *  \author cec
 */

#include "SimplifyTest.hpp"
#include "ssc/functors_for_optimizer/Serialize.hpp"
#include "ssc/functors_for_optimizer/Constant.hpp"
#include "ssc/functors_for_optimizer/Null.hpp"
#include "ssc/functors_for_optimizer/Sum.hpp"
#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/functors_for_optimizer/Divide.hpp"

using namespace ssc::functors_for_optimizer;

SimplifyTest::SimplifyTest() : a(ssc::random_data_generator::DataGenerator(22)),
                               generate(StateGenerator()),
                               x1(generate.state("x1")),
                               x2(generate.state("x2")),
                               x3(generate.state("x3"))
{
}

SimplifyTest::~SimplifyTest()
{
}

void SimplifyTest::SetUp()
{
}

void SimplifyTest::TearDown()
{
}

TEST_F(SimplifyTest, states_should_not_be_simplified)
{
    std::stringstream ss;
    Serialize v(ss);
    x1->simplify()->accept(v);
    ASSERT_EQ("x1", ss.str());
}

TEST_F(SimplifyTest, parameters_should_not_be_simplified)
{
    std::stringstream ss;
    std::stringstream ss_ref;
    Serialize v(ss);
    Parameter p(a.random<double>());
    p = a.random<double>();
    ss_ref << p.get_lambda()();
    p.simplify()->accept(v);
    ASSERT_EQ(ss_ref.str(), ss.str());
}

TEST_F(SimplifyTest, null_should_not_be_simplified)
{
    std::stringstream ss;
    Serialize v(ss);
    Null().simplify()->accept(v);
    ASSERT_EQ("0", ss.str());
}

TEST_F(SimplifyTest, simplify_sums)
{
    std::stringstream ss;
    Serialize v(ss);
    auto s = x1+x1+x2+x1;
    s->simplify()->accept(v);
    ASSERT_TRUE((ss.str()=="x2 + 3*x1") || (ss.str()=="3*x1 + x2"));
}

TEST_F(SimplifyTest, simplify_sums_bug_01)
{
    auto x4 = generate.state("x4");
    std::stringstream ss;
    Serialize v(ss);
    auto s = x1*x4*(x1+x2+x3)+x3;
    s->diff(x1)->diff(x1)->simplify()->accept(v);
    ASSERT_EQ("2*x4",ss.str());
}

TEST_F(SimplifyTest, simplify_products)
{
    std::stringstream ss;
    Serialize v(ss);
    auto s = x1*x1*x2*x1;
    s->simplify()->accept(v);
    ASSERT_TRUE((ss.str()=="x2 * x1 ^ 3") || (ss.str()=="x1 ^ 3 * x2"));
}

