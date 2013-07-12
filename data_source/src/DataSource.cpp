/*
 * DataSource.cpp
 *
 * \date 13 mars 2013, 15:31:43
 *  \author cec
 */

#include "DataSource.hpp"
#include "DataSourceException.hpp"

DataSource::DataSource() : name2module(FromName2Module()), read_only(false), signals(SignalContainer()), current_module(""), signal2module(std::tr1::unordered_map<std::string,std::string>())
{

}

FromName2Module DataSource::get_modules() const
{
    return name2module;
}

void DataSource::clear()
{
    name2module.clear();
}

ModulePtr DataSource::add_module_if_not_already_present_and_return_clone(DataSourceModule const * const module)
{
    current_module = module->get_name();
    FromName2Module::iterator it = name2module.find(current_module);
    const bool module_is_already_in_map = it != name2module.end();
    if (module_is_already_in_map)
    {
        std::string s = "A module named '";
        THROW(__PRETTY_FUNCTION__, DataSourceException, s + module->get_name() + "' already exists");
    }
    else
    {
        name2module.insert(std::make_pair(current_module, ModulePtr(module)));
    }
    FromName2Module::iterator it2 = name2module.find(current_module);
    return it2->second;
}
