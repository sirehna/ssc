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
    signals.set<double>("another signal",d);
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
    signals.set<std::string>("signal1",s1);
    signals.set<std::string>("signal2",s2);
    signals.set<std::string>("signal3",s3);
    signals.set<double>("signal1",d1);
    signals.set<double>("signal2",d2);
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

TEST_F(SignalContainerTest, should_be_able_to_convert_a_list_of_signals_to_doubles)
{

}

TEST_F(SignalContainerTest, conversion_to_doubles_should_throw_if_type_cannot_be_converted)
{

}

TEST_F(SignalContainerTest, should_be_able_to_set_double_values_for_a_set_of_signals)
{

}

TEST_F(SignalContainerTest, should_be_able_to_unset_a_signal)
{

}
