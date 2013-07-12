/*
 * SignalContainerTest.cpp
 *
 * \date 18 mars 2013, 18:00:08
 *  \author cec
 */

#include "SignalContainerTest.hpp"
#include <boost/any.hpp>

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
//! [SignalContainerTest example]
//! [SignalContainerTest expected output]
//! [SignalContainerTest expected output]
}



