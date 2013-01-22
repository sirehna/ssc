#include <iostream>
#include <random>
#include "gtest/gtest.h"
#include "Pow.hpp"
#include "StateGenerator.hpp"
#include <sstream>
#define QUOTE_ME(a) #a
#define QUOTE(a) QUOTE_ME(a)
#define COUT(a) std::cout << "in file " << __FILE__ << ", line " << __LINE__ << ": " << QUOTE(a) << " = " << a << std::endl;

TEST(sample_test_case, sample_test)
{
    StateGenerator generate;
    std::tr1::shared_ptr<State> x(generate.state("x"));
    std::cout << "x = " << x->get_name() << std::endl; 
    **x = 1;
    COUT(**x);
    EXPECT_EQ(1, 1);
}

TEST(Pow, should_be_able_to_define_x_power_something)
{
    StateGenerator generate;
    std::tr1::shared_ptr<State> x(generate.state("x"));
    std::default_random_engine generator;
    std::uniform_real_distribution<double> rnd_double(-30,30);
    std::uniform_int_distribution<size_t> rnd_exponent(0,5);
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double exp = rnd_exponent(generator);
        auto x2 = Pow(*x,exp);
        **x = rnd_double(generator);
        x2.val()();

        ASSERT_EQ(pow(**x,exp), x2.val()());
    }
}

TEST(Pow, should_be_able_to_define_grad_x_power_something)
{
    StateGenerator generate;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> rnd_double(1,30);
    std::uniform_int_distribution<size_t> rnd_exponent(1,5);
    for (size_t i = 0 ; i < 10 ; ++i)
    {
        std::stringstream ss;
        ss << i;
        COUT("");
        std::tr1::shared_ptr<State> px(generate.state(std::string("x")+ss.str()));
        const State x = *px;
        *x = rnd_double(generator);
        const double exp = rnd_exponent(generator);
        const auto x2 = Pow(x,exp);
        ASSERT_EQ(1,x2.grad().idx.size());
        ASSERT_EQ(i,x2.grad().idx.front());
        ASSERT_EQ(1,x2.grad().values.size());
        auto xx = x2.grad().values.front();
        ASSERT_DOUBLE_EQ(exp*pow(*x,exp-1.), x2.grad().values.front()());
        *x = rnd_double(generator);
        x2.val()();

        ASSERT_EQ(pow(*x,exp), x2.val()());
    }
}
