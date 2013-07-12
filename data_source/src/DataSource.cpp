/*
 * DataSource.cpp
 *
 * \date 13 mars 2013, 15:31:43
 *  \author cec
 */

#include "DataSource.hpp"
#include "DataSourceException.hpp"

class CycleException : public DataSourceException
{
    public:
        CycleException(const char* s) :
            DataSourceException(s)
        {
        }
};


DataSource::DataSource() : name2module(FromName2Module()),
                           readonly(false),
                           signals(SignalContainer()),
                           current_module(""),
                           signal2module(FromSignal2Module()),
                           module2dependantmodules(DependantModules()),
                           module2requiredsignals(DependantModules()),
                           signal2dependantmodules(DependantModules()),
                           is_up_to_date(UpdateState())
{
}

bool DataSource::read_only() const
{
    return readonly;
}

FromName2Module DataSource::get_modules() const
{
    return name2module;
}

void DataSource::clear()
{
    name2module.clear();
    signals.clear();
    current_module = "";
    signal2module.clear();
    module2dependantmodules.clear();
    module2requiredsignals.clear();
    signal2dependantmodules.clear();
    is_up_to_date.clear();
}

ModulePtr DataSource::add_module_if_not_already_present_and_return_clone(DataSourceModule const * const module)
{
    current_module = module->get_name();
    FromName2Module::iterator it = name2module.find(current_module);
    const bool module_is_already_in_map = it != name2module.end();
    if (module_is_already_in_map)
    {
        std::string s = "A module named '";
        COUT("");
        THROW(__PRETTY_FUNCTION__, DataSourceException, s + module->get_name() + "' already exists");
    }
    else
    {
        name2module.insert(std::make_pair(current_module, ModulePtr(module)));
    }
    FromName2Module::iterator it2 = name2module.find(current_module);
    is_up_to_date[current_module] = false;
    return it2->second;
}

void append(DependantModules& map, const std::string& key, const std::string& value)
{
    DependantModules::iterator it = map.find(key);
    if (it == map.end())
    {
        std::set<std::string> Value;
        Value.insert(value);
        map[key] = Value;
    }
    else it->second.insert(value);
}

void DataSource::update_module2dependantmodules()
{
    DependantModules::const_iterator it = module2requiredsignals.begin();
    for (;it!=module2requiredsignals.end();++it)
    {
        const std::set<std::string> S = it->second;
        std::set<std::string>::const_iterator it2 = S.begin();
        for (;it2!=S.end();++it2)
        {
            const FromSignal2Module::const_iterator it3 = signal2module.find(*it2);
            if (it3 != signal2module.end())
            {
                append(module2dependantmodules, it->first, it3->second);
            }
        }
    }
}

std::set<std::string> DataSource::get_dependencies(const std::string& module_name, std::set<std::string>& ret) const
{
    DependantModules::const_iterator it = module2dependantmodules.find(module_name);
    if (it != module2dependantmodules.end())
    {
        std::set<std::string> dep = it->second;
        for (std::set<std::string>::const_iterator it2 = dep.begin() ; it2 != dep.end() ; ++it2)
        {
            if (*it2 == module_name)
            {
                COUT("");
                THROW(__PRETTY_FUNCTION__, CycleException, std::string("Cycle found: module '") + module_name + std::string("' depends on itself"));
            }
            const std::set<std::string> S = get_dependencies(*it2,ret);
            if (S.find(module_name) != S.end())
            {
                COUT("");
                THROW(__PRETTY_FUNCTION__, CycleException, std::string("Cycle found: module '") + module_name + std::string("' depends on itself"));
            }
            ret.insert(S.begin(),S.end());
        }
    }
    return ret;
}

bool DataSource::a_module_depends_on_itself()
{
    try
    {
        DependantModules::iterator it = module2dependantmodules.begin();
        for (;it!= module2dependantmodules.end();++it)
        {
            get_dependencies(it->first,it->second);
        }
    }
    catch (CycleException& e)
    {
        THROW(__PRETTY_FUNCTION__, CycleException, e.what());


        return true;
    }
    return false;
}


void DataSource::update_dependencies()
{
    update_module2dependantmodules();
    if (a_module_depends_on_itself())
    {
        COUT("");
        THROW(__PRETTY_FUNCTION__, DataSourceException, std::string("Circular dependency: module '") + current_module + "' depends on itself (eventually)");
    }
}
