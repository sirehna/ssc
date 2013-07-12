/*
 * DataSourceTest.cpp
 *
 * \date 13 mars 2013, 15:19:45
 *  \author cec
 */

#include "DataSourceTest.hpp"
#include "DataSource.hpp"
#include "test_macros.hpp"
#include "gmock/gmock.h"
#include "DataSourceModule.hpp"
#include "DataSourceModuleMock.hpp"
#include "DataSourceException.hpp"

#include <set>

static DataGenerator a_(21);
static std::tr1::shared_ptr<DataSource> ds_ = std::tr1::shared_ptr<DataSource>(new DataSource());

using ::testing::Return;
using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::InSequence;

MockableDataSourceModule::MockableDataSourceModule() : DataSourceModule(ds_, a_.random<std::string>())
{

}

DataSourceTest::DataSourceTest() : a(DataGenerator(654))
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
/*
TEST_F(DataSourceTest, example)
{
//! [DataSourceTest example]
    std::tr1::shared_ptr<DataSource> ds(new DataSource);
    MockDataSourceModule m;
    EXPECT_CALL(m, initialize()).Times(1);

    ds->add<MockDataSourceModule>()

//! [DataSourceTest example]
//! [DataSourceTest expected output]
//! [DataSourceTest expected output]
}
*/

TEST_F(DataSourceTest, all_mock_modules_generated_for_tests_should_have_different_names)
{
    std::set<std::string> module_names;
    const size_t nb_of_mocks = 1000;
    for (size_t i = 0 ; i < nb_of_mocks ; ++i)
    {
        MockDataSourceModule m;
        module_names.insert(m.get_name());
    }
    ASSERT_EQ(nb_of_mocks, module_names.size());
}

TEST_F(DataSourceTest, should_be_able_to_clear_a_datasource_to_empty_it)
{
    ds_->clear();
    ASSERT_EQ(0,ds_->get_modules().size());
}

TEST_F(DataSourceTest, should_be_able_to_add_a_module_and_get_the_list_of_modules)
{
    DataSource ds;
    // Using NiceMock because we only want to specify the behavior of the method
    // of interest
    // There's a 'new' but no 'delete' because the clone() method will return
    // this pointer, therefore it will be garbage-collected by std::tr1::shared_ptr
    NiceMock<MockDataSourceModule>* m1 = new NiceMock<MockDataSourceModule>();
    NiceMock<MockDataSourceModule>* m2 = new NiceMock<MockDataSourceModule>();

    ON_CALL(*m1, clone()).WillByDefault(Return(m1));
    ON_CALL(*m2, clone()).WillByDefault(Return(m2));
    ASSERT_EQ(0,ds.get_modules().size());
    ds.add(*m1);
    ds.add(*m2);
    const FromName2Module modules = ds.get_modules();
    ASSERT_EQ(2,modules.size());
    std::set<std::string> module_names;
    std::set<std::string> expected_module_names;
    for (FromName2Module::const_iterator it = modules.begin() ; it != modules.end() ; ++it)
    {
        module_names.insert(it->first);
    }
    expected_module_names.insert(m1->get_name());
    expected_module_names.insert(m2->get_name());
    ASSERT_EQ(expected_module_names, module_names);
}

TEST_F(DataSourceTest, check_that_the_correct_functions_are_called_for_add_module)
{
    DataSource ds;
    // We want the calls to occur in an exact order
    InSequence s;
    // We're using a StrictMock because we want to capture the behavior of
    // DataSource::add exactly (i.e. there should not be *any* uninteresting
    // calls)
    // There's a 'new' but no 'delete' because the clone() method will return
    // this pointer, therefore it will be garbage-collected by std::tr1::shared_ptr

    StrictMock<MockDataSourceModuleWithGetName>* m = new StrictMock<MockDataSourceModuleWithGetName>();
    ON_CALL(*m, clone()).WillByDefault(Return(m));
    EXPECT_CALL(*m, clone()).Times(1);
    EXPECT_CALL(*m, get_name()).Times(1);
    EXPECT_CALL(*m, initialize()).Times(1);
    EXPECT_CALL(*m, update()).Times(1);
    ds.add(*m);
}

TEST_F(DataSourceTest, should_not_be_able_to_add_two_modules_with_the_same_name)
{
    DataSource ds;
    // Using NiceMock because we only want to specify the behavior of the method
    // of interest
    NiceMock<MockDataSourceModuleWithGetName>* m = new NiceMock<MockDataSourceModuleWithGetName>();
    ON_CALL(*m, clone()).WillByDefault(Return(m));
    ds.add(*m);
    ASSERT_THROW(ds.add(*m),DataSourceException);
}
