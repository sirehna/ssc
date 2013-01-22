#include "ParameterTest.hpp"
#include "Parameter.hpp"

ParameterTest::ParameterTest() : a(DataGenerator(65489745))
{
}

void ParameterTest::SetUp()
{
}

void ParameterTest::TearDown()
{
}

TEST_F(ParameterTest, should_be_able_to_change_value_of_a_parameter)
{
    Parameter p(321);
    ASSERT_EQ(321, *p);
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const double value = a.random<double>();
        *p = value;
        ASSERT_EQ(value, *p);
    }
}

