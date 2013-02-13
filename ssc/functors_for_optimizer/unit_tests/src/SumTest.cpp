/*
 * SumTest.cpp
 *
 * \date 31 janv. 2013, 16:02:15
 *  \author cec
 */

#include "SumTest.hpp"
#include "StateGenerator.hpp"
#include "Sum.hpp"
#include "Constant.hpp"
#include "FunctorAlgebra.hpp"
#include "Serialize.hpp"

SumTest::SumTest() : a(DataGenerator(12)), generate(StateGenerator())
{
}

SumTest::~SumTest()
{
}

void SumTest::SetUp()
{
}

void SumTest::TearDown()
{
}

TEST_F(SumTest, example)
{
//! [SumTest example]
    StateGenerator generate;
    auto x = generate.state("x");
    auto y = generate.state("y");
    Sum s(x,y);
//! [SumTest example]
//! [SumTest expected output]
    for (size_t i = 0 ; i<1000 ; ++i)
    {
        const double v1 = a.random<double>();
        const double v2 = a.random<double>();
        **x = v1;
        **y = v2;
        ASSERT_DOUBLE_EQ(v1+v2,s.get_value()());
    }
//! [SumTest expected output]
}

TEST_F(SumTest, derivative)
{
    StateGenerator generate;
    auto x = generate.state("x");
    auto y = generate.state("y");
    Sum s(x,y);
    ASSERT_EQ(1,s.diff(x)->get_value()());
    ASSERT_EQ(1,s.diff(y)->get_value()());
}

TEST_F(SumTest, comparison_to_constant_bug)
{
    ConstantPtr c(new Constant(1));
    std::vector<NodePtr> nodes(1,c);
    SumPtr one(new Sum(nodes));
    ASSERT_EQ(1, one);
}

