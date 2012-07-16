#include "random_data_generator_tests.hpp"
#include <set>

void DataGeneratorTests::SetUp()
{
}

void DataGeneratorTests::TearDown()
{
}

TEST_F(DataGeneratorTests, should_have_a_random_data_generator_for_doubles)
{
    std::set<double> S;
    const size_t nb_of_trials = 100;
    for (size_t i =0 ; i < nb_of_trials ; ++i)
    {
        S.clear();
        const size_t nb_of_values_to_generate = a.random_size_t(1,100);
        for (size_t j = 0 ; j < nb_of_values_to_generate ; ++j)
        {
            S.insert(a.random<double>()());
        }
        ASSERT_EQ(nb_of_values_to_generate, S.size());
    }
}

TEST_F(DataGeneratorTests, should_have_a_random_data_generator_for_vector_of_doubles)
{
    std::set<std::vector<double> > S;
    const size_t nb_of_trials = 100;
    for (size_t i =0 ; i < nb_of_trials ; ++i)
    {
        S.clear();
        const size_t nb_of_values_to_generate = a.random_size_t(1,5);
        for (size_t j = 0 ; j < nb_of_values_to_generate ; ++j)
        {
            const std::vector<double> v = a.random_vector_of<double>().of_size(3)();
            ASSERT_FALSE(v.empty());
            S.insert(v);
        }
        ASSERT_EQ(nb_of_values_to_generate, S.size());
    }

}

TEST_F(DataGeneratorTests, should_be_able_to_generate_doubles_greater_than_a_value)
{
    const size_t nb_of_trials = 100;
    std::vector<double> v(nb_of_trials);
    for (size_t i = 0 ; i < nb_of_trials ; ++i)
    {
        const double lower_bound = a.random<double>()();
        ASSERT_GE(a.random<double>().greater_than(lower_bound)(), lower_bound);
    }
}

TEST_F(DataGeneratorTests, should_be_able_to_generate_doubles_no_greater_than_a_value)
{
    const size_t nb_of_trials = 100;
    std::vector<double> v(nb_of_trials);
    for (size_t i = 0 ; i < nb_of_trials ; ++i)
    {
        const double upper_bound = a.random<double>()();
        ASSERT_LE(a.random<double>().no().greater_than(upper_bound)(), upper_bound);
    }
}

TEST_F(DataGeneratorTests, should_be_able_to_generate_a_vector_of_doubles_greater_than_a_value)
{
    const size_t nb_of_trials = 100;
    std::vector<double> v(nb_of_trials);
    for (size_t i = 0 ; i < nb_of_trials ; ++i)
    {
        const double lower_bound = a.random<double>()();
        const size_t n = a.random<size_t>().no().greater_than(20)();
        const std::vector<double> v = a.random_vector_of<double>().of_size(n).greater_than(lower_bound)();
        for (std::vector<double>::const_iterator it = v.begin() ; it != v.end() ; ++it)
        {
            ASSERT_GE(*it, lower_bound);
        }
    }
}

TEST_F(DataGeneratorTests, should_be_able_to_generate_a_vector_of_doubles_no_greater_than_a_value)
{
    const size_t nb_of_trials = 100;
    std::vector<double> v(nb_of_trials);
    for (size_t i = 0 ; i < nb_of_trials ; ++i)
    {
        const double upper_bound = a.random<double>()();
        const size_t n = a.random<size_t>().no().greater_than(20)();
        const std::vector<double> v = a.random_vector_of<double>().of_size(n).no().greater_than(upper_bound)();
        for (std::vector<double>::const_iterator it = v.begin() ; it != v.end() ; ++it)
        {
            ASSERT_LE(*it, upper_bound);
        }
    }
}

TEST_F(DataGeneratorTests, should_be_able_to_generate_doubles_between_two_values)
{
    const size_t nb_of_trials = 100;
    for (size_t i = 0 ; i < nb_of_trials ; ++i)
    {
        const double lower_bound = a.random<double>()();
        const double upper_bound = a.random<double>().greater_than(lower_bound)();
        ASSERT_LE(a.random<double>().between(lower_bound,upper_bound)(), upper_bound);
        ASSERT_GE(a.random<double>().between(lower_bound,upper_bound)(), lower_bound);
    }
}

TEST_F(DataGeneratorTests, should_be_able_to_generate_doubles_outside_an_interval)
{
    const size_t nb_of_trials = 100;
    std::set<double> generated_numbers;
    for (size_t i = 0 ; i < nb_of_trials ; ++i)
    {
        const double number1 = a.random<double>().outside(2.1,2.9).but().between(2,3)();
        const double number2 = a.random<double>().between(2,3).but().outside(2.1,2.9)();
        ASSERT_LT(number1, 3);
        ASSERT_GT(number1, 2);
        ASSERT_FALSE((number1>=2.1)&&(number1<=2.9));
        ASSERT_LT(number2, 3);
        ASSERT_GT(number2, 2);
        ASSERT_FALSE((number2>=2.1)&&(number2<=2.9));
        generated_numbers.insert(number1);
        generated_numbers.insert(number2);
    }
    ASSERT_EQ(generated_numbers.size(), 2*nb_of_trials);
}

TEST_F(DataGeneratorTests, should_return_zero_if_forbidden_interval_matches_allowed_interval)
{
    const size_t nb_of_trials = 100;
    for (size_t i = 0 ; i < nb_of_trials ; ++i)
    {
        const double min_bound = a.random<double>()();
        const double max_bound = a.random<double>().greater_than(min_bound)();
        ASSERT_EQ(a.random<double>().between(min_bound,max_bound).but().outside(min_bound,max_bound)(),0);
    }
}



TEST_F(DataGeneratorTests, should_be_able_to_generate_size_ts_for_all_but_one_value)
{
    const size_t nb_of_trials = 100;
    for (size_t i = 0 ; i < nb_of_trials ; ++i)
    {
        const size_t lower_bound = a.random<size_t>().between(1,5)();
        const size_t upper_bound = a.random<size_t>().between(1,5).greater_than(lower_bound)();
        const size_t forbidden = a.random<size_t>().between(lower_bound, upper_bound)();
        const size_t number = a.random<size_t>().between(lower_bound, upper_bound).but_not(forbidden)();
        ASSERT_NE(number, forbidden);
    }
}

TEST_F(DataGeneratorTests, should_be_able_to_generate_a_random_double)
{
    const size_t nb_of_trials = 100;
    std::set<double> generated_numbers;
    for (size_t i = 0 ; i < nb_of_trials ; ++i)
    {
        generated_numbers.insert(a.random<bool>()());
    }
    ASSERT_EQ(generated_numbers.size(), 2);
}
