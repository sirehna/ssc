#include "StateTest.hpp"
#include "State.hpp"

StateTest::StateTest() : a(DataGenerator(581424))
{
}

void StateTest::SetUp()
{
}

void StateTest::TearDown()
{
}

TEST_F(StateTest, should_have_one_and_only_one_constructor_which_takes_the_name_and_index_as_parameters)
{
    const std::string name = a.random<std::string>();
    const size_t index = a.random<size_t>();
    const State x(name, index);
    ASSERT_EQ(name, x.get_name());
    ASSERT_EQ(index, x.get_index());
    const double value = a.random<double>();
    *x = value;
    ASSERT_EQ(value, *x);
}

TEST_F(StateTest, should_be_able_to_compare_two_states)
{
    const std::string a_name = a.random<std::string>();
    const std::string another_name = a.random<std::string>();
    const size_t an_index = a.random<size_t>();
    const size_t another_index = a.random<size_t>().but_not(an_index);
    const State x(a_name, an_index);
    const State y(another_name, an_index);
    const State z(a_name, another_index);
    const State t(another_name, another_index);
    const State u(a_name, an_index);

    ASSERT_EQ(x,x);
    ASSERT_EQ(y,y);
    ASSERT_EQ(z,z);
    ASSERT_EQ(t,t);

    ASSERT_NE(x,y);
    ASSERT_NE(y,x);
    ASSERT_NE(x,z);
    ASSERT_NE(z,x);
    ASSERT_NE(t,x);
    ASSERT_NE(x,t);
    ASSERT_NE(y,z);
    ASSERT_NE(y,t);
    ASSERT_NE(z,t);
    ASSERT_NE(x,u);
    ASSERT_NE(u,x);
}

TEST_F(StateTest, should_be_able_to_sort_states_by_index)
{
    const State x("azertx", 2);
    const State w("azertw", 3);
    const State z("azertz", 1);
    const State y("azerty", 3);

    ASSERT_LT(x,y);
    ASSERT_LT(x,w);
    ASSERT_LT(z,y);
    ASSERT_LT(z,w);
}

TEST_F(StateTest, derivative_zero_or_one)
{
    const StatePtr x(new State("x", 1));
    const StatePtr y(new State("y", 1));
    ASSERT_EQ(1, x->diff(x)->get_value()());
    ASSERT_EQ(1, y->diff(y)->get_value()());
    ASSERT_EQ(0, x->diff(y)->get_value()());
    ASSERT_EQ(0, y->diff(x)->get_value()());
}
