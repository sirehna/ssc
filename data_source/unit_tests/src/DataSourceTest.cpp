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
#include "TestModules.hpp"

#include <set>

static DataGenerator a_(21);
static DataSource* ds_;

using ::testing::Return;
using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::InSequence;

MockableDataSourceModule::MockableDataSourceModule() : DataSourceModule(ds_, a_.random<std::string>())
{

}

DataSourceTest::DataSourceTest() : a(DataGenerator(654))
{
    ds_ = new DataSource();
}

DataSourceTest::~DataSourceTest()
{
    delete ds_;
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
        MockDataSourceModule mock;
        module_names.insert(mock.get_name());
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
    NiceMock<MockDataSourceModule>* mock_1 = new NiceMock<MockDataSourceModule>();
    NiceMock<MockDataSourceModule>* mock_2 = new NiceMock<MockDataSourceModule>();

    ON_CALL(*mock_1, clone()).WillByDefault(Return(mock_1));
    ON_CALL(*mock_2, clone()).WillByDefault(Return(mock_2));
    ASSERT_EQ(0,ds.get_modules().size());
    ds.add(*mock_1);
    ds.add(*mock_2);
    const FromName2Module modules = ds.get_modules();
    ASSERT_EQ(2,modules.size());
    std::set<std::string> module_names;
    std::set<std::string> expected_module_names;
    for (FromName2Module::const_iterator it = modules.begin() ; it != modules.end() ; ++it)
    {
        module_names.insert(it->first);
    }
    expected_module_names.insert(mock_1->get_name());
    expected_module_names.insert(mock_2->get_name());
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

    StrictMock<MockDataSourceModuleWithGetName>* mock = new StrictMock<MockDataSourceModuleWithGetName>();
    ON_CALL(*mock, clone()).WillByDefault(Return(mock));
    EXPECT_CALL(*mock, clone()).Times(1);
    EXPECT_CALL(*mock, get_name()).Times(1);
    EXPECT_CALL(*mock, initialize()).Times(1);
    EXPECT_CALL(*mock, update()).Times(1);
    ds.add(*mock);
}

TEST_F(DataSourceTest, should_not_be_able_to_add_two_modules_with_the_same_name)
{
    DataSource ds;
    // Using NiceMock because we only want to specify the behavior of the method
    // of interest
    NiceMock<MockDataSourceModuleWithGetName>* mock = new NiceMock<MockDataSourceModuleWithGetName>();
    ON_CALL(*mock, clone()).WillByDefault(Return(mock));
    ds.add(*mock);
    ASSERT_THROW(ds.add(*mock),DataSourceException);
}

TEST_F(DataSourceTest, should_be_able_to_set_and_retrieve_a_constant)
{
    DataSource ds;
    for (size_t i = 0 ; i < 10000 ; ++i)
    {
        const double d = a.random<double>();
        ds.set("d", d);
        ASSERT_DOUBLE_EQ(d, ds.get<double>("d"));
    }
}

TEST_F(DataSourceTest, a_module_cannot_depend_on_itself)
{
    DataSource ds;
    ASSERT_THROW(ds.add<ModuleDependingOnItself>(a.random<std::string>()), DataSourceException);
}

TEST_F(DataSourceTest, should_throw_if_module_name_is_empty)
{
    DataSource ds;
    ASSERT_THROW(ds.add<TestModule>(""), DataSourceException);
}

TEST_F(DataSourceTest, should_throw_if_there_are_any_circular_dependencies)
{
    DataSource ds;
    ds.add<ModuleA>("Module A");
    ds.add<ModuleB>("Module B");
    ASSERT_THROW(ds.add<ModuleC>("Module C"), DataSourceException);
}

TEST_F(DataSourceTest, should_throw_if_attempting_to_retrieve_a_value_not_in_DataSource)
{
    DataSource ds;
    ASSERT_THROW(ds.get<double>(a.random<std::string>()), DataSourceException);
}

TEST_F(DataSourceTest, should_throw_if_not_all_dependencies_are_met)
{
    DataSource ds;
    ds.add<TestModule>(a.random<std::string>());
    ASSERT_THROW(ds.get<size_t>("nb_of_updates"), DataSourceException);
    ds.set<size_t>("nb_of_updates", 0);
    ASSERT_NO_THROW(ds.get<size_t>("nb_of_updates"));
}

TEST_F(DataSourceTest, should_throw_if_two_modules_set_the_same_signal)
{
    DataSource ds;
    ds.add<TestModule>(a.random<std::string>());
    ASSERT_THROW(ds.add<TestModule>(a.random<std::string>()), DataSourceException);
}

TEST_F(DataSourceTest, test_module_should_work_properly)
{
    DataSource ds;
    ds.add<TestModule>(a.random<std::string>());
    const size_t i = a.random<size_t>();
    ds.set<size_t>("nb_of_updates", i);
    ASSERT_EQ(i+1, ds.get<size_t>("nb_of_updates2"));
}

TEST_F(DataSourceTest, data_source_should_not_update_unnecessarily)
{
    DataSource ds;
    ds.add<TestModule>(a.random<std::string>());
    const size_t i = a.random<size_t>();
    ds.set<size_t>("nb_of_updates", i);
    for (size_t k = 0 ; k < 10000 ; ++k)
    {
        ASSERT_EQ(i+1, ds.get<size_t>("nb_of_updates2"));
    }
    ds.set<size_t>("nb_of_updates", i+1);
    ASSERT_EQ(i+2, ds.get<size_t>("nb_of_updates2"));
}

TEST_F(DataSourceTest, two_signals_with_same_name_but_different_types_do_not_create_a_circular_dependencies)
{
    DataSource ds;
    ASSERT_NO_THROW(ds.add<ModuleD>("Module D"));
}

DECLARE_MODULE(M1)
DECLARE_MODULE(M2)
DECLARE_MODULE(M3)

void M2::update() const
{
    ds->get<double>("s1");
    ds->set<double>("s2", 0);
}

void M3::update() const
{
    ds->get<double>("s2");
}

void M1::update() const
{
    ds->set<double>("s1",0);
}

TEST_F(DataSourceTest, bug_detected_in_EONAV_for_cyclic_dependency_check)
{
    DataSource data_source;
    data_source.add<M1>("m1");
    data_source.add<M2>("m2");
    ASSERT_NO_THROW(data_source.add<M3>("m3"));
}
