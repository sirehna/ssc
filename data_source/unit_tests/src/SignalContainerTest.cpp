/*
 * SignalContainerTest.cpp
 *
 * \date 18 mars 2013, 18:00:08
 *  \author cec
 */

#include "SignalContainerTest.hpp"
#include "SignalContainer.hpp"
#include "test_macros.hpp"

SignalContainerTest::SignalContainerTest() : a(DataGenerator(19))
{
}

SignalContainerTest::~SignalContainerTest()
{
}

void SignalContainerTest::SetUp()
{
}

void SignalContainerTest::TearDown()
{
}

TEST_F(SignalContainerTest, example)
{
//! [SignalContainerTest example]
    SignalContainer signals;
    const std::string s = a.random<std::string>();
    signals.set<std::string>("signal name",s);
    const double d = a.random<double>();
    signals.set("another signal",d);
//! [SignalContainerTest example]
//! [SignalContainerTest expected output]
    ASSERT_EQ(s, signals.get<std::string>("signal name"));
    ASSERT_DOUBLE_EQ(d, signals.get<double>("another signal"));
//! [SignalContainerTest expected output]
}

TEST_F(SignalContainerTest, should_throw_if_retrieving_an_inexistent_signal)
{
    SignalContainer signals;
    ASSERT_THROW(signals.get<double>(a.random<std::string>()), SignalContainerException);
}

TEST_F(SignalContainerTest, method_get_should_throw_if_signal_has_incorrect_return_type)
{
    SignalContainer signals;
    signals.set<std::string>("signal name",a.random<std::string>());
    ASSERT_THROW(signals.get<double>("signal name"), SignalContainerException);
}


TEST_F(SignalContainerTest, should_be_able_to_retrieve_all_signals_of_a_given_type)
{
    SignalContainer signals;
    const std::string s1 = a.random<std::string>();
    const std::string s2 = a.random<std::string>();
    const std::string s3 = a.random<std::string>();
    const double d1 = a.random<double>();
    const double d2 = a.random<double>();
    signals.set("signal1",s1);
    signals.set("signal2",s2);
    signals.set("signal3",s3);
    signals.set("signal1",d1);
    signals.set("signal2",d2);
    std::map<std::string,std::string> string_signals = signals.get_all<std::string>();
    std::map<std::string,double> double_signals = signals.get_all<double>();
    ASSERT_EQ(3, string_signals.size());
    ASSERT_EQ(2, double_signals.size());
    ASSERT_EQ(s1, string_signals["signal1"]);
    ASSERT_EQ(s2, string_signals["signal2"]);
    ASSERT_EQ(s3, string_signals["signal3"]);
    ASSERT_EQ(d1, double_signals["signal1"]);
    ASSERT_EQ(d2, double_signals["signal2"]);
}



TEST_F(SignalContainerTest, should_be_able_to_retrieve_names_of_all_types_in_SignalContainer)
{
    SignalContainer signals;
    const size_t n = a.random<size_t>().no().greater_than(20);
    const double d1 = a.random<double>();
    const double d2 = a.random<double>();
    const std::vector<double> vd = a.random_vector_of<double>().of_size(n);
    const float f1 = a.random<float>();
    const float f2 = a.random<float>();
    const std::vector<float> vf = a.random_vector_of<float>().of_size(n);
    const int i1 = a.random<int>();
    const int i2 = a.random<int>();
    const std::vector<int> vi = a.random_vector_of<int>().of_size(n);
    const size_t s1 = a.random<size_t>();
    const size_t s2 = a.random<size_t>();
    const std::vector<size_t> vs = a.random_vector_of<size_t>().of_size(n);

    signals.set(a.random<std::string>(),d1);
    signals.set(a.random<std::string>(),d2);
    signals.set(a.random<std::string>(),vd);
    signals.set(a.random<std::string>(),f1);
    signals.set(a.random<std::string>(),f2);
    signals.set(a.random<std::string>(),vf);
    signals.set(a.random<std::string>(),i1);
    signals.set(a.random<std::string>(),i2);
    signals.set(a.random<std::string>(),vi);
    signals.set(a.random<std::string>(),s1);
    signals.set(a.random<std::string>(),s2);
    signals.set(a.random<std::string>(),vs);
}
/*
TEST_F(SignalContainerTest, should_be_able_to_retrieve_all_doubles_in_a_single_list)
{
    SignalContainer signals;
    const size_t n = a.random<size_t>().no().greater_than(20);
    const double d1 = a.random<double>();
    const double d2 = a.random<double>();
    const std::vector<double> vd = a.random_vector_of<double>().of_size(n);
    const float f1 = a.random<float>();
    const float f2 = a.random<float>();
    const std::vector<float> vf = a.random_vector_of<float>().of_size(n);
    const int i1 = a.random<int>();
    const int i2 = a.random<int>();
    const std::vector<int> vi = a.random_vector_of<int>().of_size(n);
    const size_t s1 = a.random<size_t>();
    const size_t s2 = a.random<size_t>();
    const std::vector<size_t> vs = a.random_vector_of<size_t>().of_size(n);

    signals.set("signal1",d1);
    signals.set("signal3",d2);
    signals.set("signal2",vd);
    signals.set("signal5",f1);
    signals.set("signal7",f2);
    signals.set("signal4",vf);
    signals.set("signal6",i1);
    signals.set("signal9",i2);
    signals.set("signal8",vi);
    signals.set("signal10",s1);
    signals.set("signal11",s2);
    signals.set("signal12",vs);
    std::list<double> s = signals.to_doubles();
    ASSERT_EQ(4*(2+n), s.size());
    ASSERT_DOUBLE_EQ(d1, s.front());s.pop_front();
    for (size_t k = 0 ; k < n ; ++k)
    {
        ASSERT_DOUBLE_EQ(vd.at(k), s.front());s.pop_front();
    }
    for (size_t k = 0 ; k < n ; ++k)
    {
        ASSERT_DOUBLE_EQ(vf.at(k), s.front());s.pop_front();
    }
    ASSERT_DOUBLE_EQ(f1, s.front());s.pop_front();
    ASSERT_DOUBLE_EQ(i1, s.front());s.pop_front();
    ASSERT_DOUBLE_EQ(f2, s.front());s.pop_front();
    for (size_t k = 0 ; k < n ; ++k)
    {
        ASSERT_DOUBLE_EQ(vi.at(k), s.front());s.pop_front();
    }
    ASSERT_DOUBLE_EQ(i2, s.front());s.pop_front();
    ASSERT_DOUBLE_EQ(s1, s.front());s.pop_front();
    ASSERT_DOUBLE_EQ(s2, s.front());s.pop_front();
    for (size_t k = 0 ; k < n ; ++k)
    {
        ASSERT_DOUBLE_EQ(vs.at(k), s.front());s.pop_front();
    }
}

TEST_F(SignalContainerTest, coercion_should_work_even_if_SignalContainer_contains_non_coercible_types)
{
ASSERT_TRUE(false);
}

TEST_F(SignalContainerTest, can_define_coercion_for_user_defined_types)
{
    struct T1 {double a;double b;size_t c;};
ASSERT_TRUE(false);
}
*/
