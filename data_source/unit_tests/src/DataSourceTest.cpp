/*
 * DataSourceTest.cpp
 *
 * \date 13 mars 2013, 15:19:45
 *  \author cec
 */

#include "DataSourceTest.hpp"
#include "DataSource.hpp"
#include "test_macros.hpp"

DataSourceTest::DataSourceTest() : a(DataGenerator(21))
{
}

DataSourceTest::~DataSourceTest()
{
}

void DataSourceTest::SetUp()
{
}

void DataSourceTest::TearDown()
{
}

TEST_F(DataSourceTest, example)
{
//! [DataSourceTest example]
    DataSource ds;
//! [DataSourceTest example]
//! [DataSourceTest expected output]
//! [DataSourceTest expected output]
}



