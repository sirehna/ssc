#include "PowTest.hpp"
#include "Pow.hpp"
#include "StateGenerator.hpp"

PowTest::PowTest() : a(DataGenerator(171429))
{
}

void PowTest::SetUp()
{
}

void PowTest::TearDown()
{
}


TEST_F(PowTest, should_be_able_to_define_x_power_something)
{
    StateGenerator generate;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const State x = generate.state(a.random<std::string>());
        *x = a.random<double>().between(-20,20);
        const double exp = a.random<double>().between(-5,5);
        const auto x2 = Pow(x,exp);
        ASSERT_EQ(pow(*x,exp), x2.val()());
    }
}

TEST_F(PowTest, should_be_able_to_define_grad_x_power_something)
{
    StateGenerator generate;
    for (size_t i = 0 ; i < 10 ; ++i)
    {
        State x = generate.state(a.random<std::string>());
        *x = a.random<double>().between(2,20);
        const double exp = a.random<double>().between(-5,5);
        const auto x2 = Pow(x,exp);
        ASSERT_EQ(1,x2.grad().idx.size());
        ASSERT_EQ(i,x2.grad().idx.front());
        ASSERT_EQ(1,x2.grad().values.size());
        ASSERT_DOUBLE_EQ(exp*pow(*x,exp-1.), x2.grad().values.front()());
    }
}

TEST_F(PowTest, should_be_able_to_define_hes_x_power_something)
{
    StateGenerator generate;
    for (size_t i = 0 ; i < 10 ; ++i)
    {
        State x = generate.state(a.random<std::string>());
        *x = a.random<double>().between(2,20);
        const double exp = a.random<double>().between(-5,5);
        const auto x2 = Pow(x,exp);
        ASSERT_EQ(1,x2.hes().row_idx.size());
        ASSERT_EQ(i,x2.hes().row_idx.front());
        ASSERT_EQ(1,x2.hes().col_idx.size());
        ASSERT_EQ(i,x2.hes().col_idx.front());
        ASSERT_EQ(1,x2.hes().values.size());
        ASSERT_DOUBLE_EQ(exp*(exp-1.)*pow(*x,exp-2.), x2.hes().values.front()());
    }
}
