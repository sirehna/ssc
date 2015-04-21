#include "StateGeneratorTest.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

#include "ssc/macros/tr1_macros.hpp"
#include TR1INC(memory)

typedef TR1(shared_ptr)<State> StateShrdPtr;

StateGeneratorTest::StateGeneratorTest() : a(ssc::random_data_generator::DataGenerator(171429))
{
}

void StateGeneratorTest::SetUp()
{
}

void StateGeneratorTest::TearDown()
{
}

TEST_F(StateGeneratorTest, should_be_able_to_generate_a_state_with_a_given_name)
{
    StateGenerator generate;
    const std::string name = a.random<std::string>();
    auto x = generate.state(name);
    ASSERT_EQ(name, x->get_name());
}

TEST_F(StateGeneratorTest, state_indexes_should_correspond_to_order_of_creation)
{
    StateGenerator generate;
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const auto state = generate.state(a.random<std::string>());
        ASSERT_EQ(i, state->get_index());
    }
}

TEST_F(StateGeneratorTest, cannot_build_two_states_with_the_same_name)
{
    StateGenerator generate;
    const std::string name = a.random<std::string>();
    generate.state(name);
    ASSERT_THROW(generate.state(name), StateGeneratorException);
}

TEST_F(StateGeneratorTest, can_reset_state_generator)
{
    StateGenerator generate;
    const std::string name = a.random<std::string>();
    generate.state(name);
    generate.reset();
    ASSERT_NO_THROW(generate.state(name));
}

