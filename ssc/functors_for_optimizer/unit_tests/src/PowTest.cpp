#include "PowTest.hpp"
#include "ssc/macros/extra_test_assertions.hpp"
#include "ssc/macros/tr1_macros.hpp"
#include "ssc/functors_for_optimizer/Pow.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"
#include "ssc/functors_for_optimizer/Parameter.hpp"
#include "ssc/functors_for_optimizer/Serialize.hpp"

using namespace ssc::functors_for_optimizer;

PowTest::PowTest() : a(ssc::random_data_generator::DataGenerator(171429)), generate(StateGenerator())
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
    const double EPS = 1e-13;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const auto x = generate.state(a.random<std::string>());
        *x = a.random<double>().between(0.1,20);
        const double exp = a.random<double>().between(-5,5);
        const auto x2 = Pow(x,exp);
        const double expected = pow(x->get_lambda()(),exp);
        const double actual = x2.get_lambda()();
        ASSERT_SMALL_RELATIVE_ERROR(expected, actual, EPS);
        generate.reset();
    }
}

TEST_F(PowTest, derivative)
{
    const auto x = generate.state("x");
    const auto n = generate.parameter(10);
    const auto x_pow_n = Pow(x,n);
    const auto dpow = x_pow_n.diff(x)->get_lambda();

    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *x = a.random<double>().between(0,20);
        *n = a.random<double>().between(1,5);
        ASSERT_DOUBLE_EQ((n->get_lambda()())*pow(x->get_lambda()(),(n->get_lambda()())-1), dpow());
    }
}
