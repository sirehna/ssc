class MockDataSourceModule : public MockableDataSourceModule
{
    public:
        MOCK_CONST_METHOD0(clone, std::tr1::shared_ptr<DataSourceModule>());
        MOCK_METHOD1(set_all, void(const bool&));
};

class MockDataSourceModuleWithGetName : public MockableDataSourceModule
{
    public:
        MOCK_CONST_METHOD0(clone, std::tr1::shared_ptr<DataSourceModule>());
        MOCK_METHOD1(set_all, void(const bool&));
        MOCK_CONST_METHOD0(get_name, std::string());
};
