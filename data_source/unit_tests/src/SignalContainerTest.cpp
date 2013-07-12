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
#include <vector>
TEST_F(SignalContainerTest, example)
{
//! [SignalContainerTest example]
    SignalContainer signals;
    const std::string s = a.random<std::string>();
    signals.add<std::string>("signal name",s);
    const double d = a.random<double>();
    signals.add<double>("another signal",d);
//! [SignalContainerTest example]
//! [SignalContainerTest expected output]
    ASSERT_EQ(s, signals.get<std::string>("signal name"));
    ASSERT_DOUBLE_EQ(d, signals.get<double>("another signal"));
//! [SignalContainerTest expected output]
}



