/*
 * DataSource.cpp
 *
 * \date 13 mars 2013, 15:31:43
 *  \author cec
 */

#include "DataSource.hpp"
#include "DataSourceException.hpp"
#include <iostream>
#include <sstream>

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
                           module_being_updated(""),
                           signal2module(FromSignal2Module()),
                           module2dependantmodules(DependantModules()),
                           module2requiredmodules(DependantModules()),
                           module2requiredsignals(DependantModules()),
                           signal2dependantmodules(DependantModules()),
                           is_up_to_date(UpdateState())
{
}

std::string DataSource::draw() const
{
    std::stringstream ss;
    ss << "DataSource:";
    ss << "\texported_signals_by_each_module" << std::endl;
    for (FromSignal2Module::const_iterator it = signal2module.begin() ; it != signal2module.end() ; ++it)
    {
        ss << "\t\t" << it->second << " -> [" << it->first << "]" << std::endl;
    }
    ss << "\tsignals_required_by_each_module" << std::endl;
    for (DependantModules::const_iterator it = module2requiredsignals.begin() ; it != module2requiredsignals.end() ; ++it)
    {
        ss << "\t\t[ ";
        for (std::set<std::string>::const_iterator it2 = it->second.begin() ; it2 != it->second.end() ; ++it2)
        {
            ss << "'" << *it2 << "' ";
        }
        ss << "] -> " << it->first << std::endl;
    }
    return ss.str();
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

ModulePtr DataSource::add_module_if_not_already_present_and_return_clone(const DataSourceModule& module)
{
    FromName2Module::iterator it = name2module.find(module.get_name());
    const bool module_is_already_in_map = it != name2module.end();
                COUT(module_is_already_in_map);
    if (module_is_already_in_map)
    {
        std::string s = "A module named '";
                COUT("");
        THROW(__PRETTY_FUNCTION__, DataSourceException, s + module.get_name() + "' already exists");
    }
    COUT("");
    ModulePtr ret(module.clone());
    COUT("");
    current_module = module.get_name();
    COUT("");
    name2module.insert(std::make_pair(current_module, ret));
    COUT("");
    is_up_to_date[current_module] = false;
    COUT("");
    return ret;
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

void DataSource::add_dependencies_and_dependent_modules(const std::set<std::string>& required_signals, const std::string& module_using_signals)
{
    std::set<std::string>::const_iterator that_required_signal = required_signals.begin();
    for (; that_required_signal != required_signals.end(); ++that_required_signal)
    {
        const FromSignal2Module::const_iterator it = signal2module.find(*that_required_signal);
        if (it != signal2module.end())
        {
            const std::string module_producing_signal = it->second;
            append(module2requiredmodules, module_using_signals, module_producing_signal);
            append(module2dependantmodules, module_producing_signal, module_using_signals);
        }
    }

}

std::set<std::string> DataSource::get_dependencies(const std::string& ref_module, const std::string& current_module, std::set<std::string>& dependencies) const
{
    DependantModules::const_iterator that_module = module2dependantmodules.find(current_module);
    if (that_module != module2dependantmodules.end())
    {
        std::set<std::string> dependant_modules = that_module->second;
        for (std::set<std::string>::const_iterator that_dependant_module = dependant_modules.begin() ; that_dependant_module != dependant_modules.end() ; ++that_dependant_module)
        {
            if (*that_dependant_module == ref_module)
            {
                THROW(__PRETTY_FUNCTION__, CycleException, std::string("Cycle found: module '") + ref_module + std::string("' depends on itself"));
            }
            const std::set<std::string> new_dependencies = get_dependencies(ref_module,*that_dependant_module,dependencies);
            dependencies.insert(new_dependencies.begin(),new_dependencies.end());
            if (dependencies.find(ref_module) != dependencies.end())
            {
                THROW(__PRETTY_FUNCTION__, CycleException, std::string("Module '") + ref_module + "' depends on itself");
            }
        }
    }
    return dependencies;
}

std::set<std::string> DataSource::get_dependencies(const std::string& module, std::set<std::string>& dependencies) const
{
    return get_dependencies(module,module, dependencies);
}

bool DataSource::a_module_depends_on_itself()
{
    DependantModules::iterator it = module2dependantmodules.begin();
    for (;it!= module2dependantmodules.end();++it)
    {
        //std::set<std::string>::const_iterator dependent_module = it->second.begin();
        get_dependencies(it->first,it->second);
    }
    return false;
}


void DataSource::update_dependencies()
{
    DependantModules::const_iterator module_requirements_pair = module2requiredsignals.begin();
    for (;module_requirements_pair!=module2requiredsignals.end();++module_requirements_pair)
    {
        const std::set<std::string> required_signals = module_requirements_pair->second;
        const std::string module_using_signals = module_requirements_pair->first;
        add_dependencies_and_dependent_modules(required_signals, module_using_signals);
    }
    if (a_module_depends_on_itself())
    {
        THROW(__PRETTY_FUNCTION__, DataSourceException, std::string("Circular dependency: module '") + current_module + "' depends on itself (eventually)");
    }
}
