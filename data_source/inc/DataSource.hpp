/*
 * DataSource.hpp
 *
 * \date 13 mars 2013, 15:31:43
 *  \author cec
 */

#ifndef DATASOURCE_HPP_
#define DATASOURCE_HPP_

#include <tr1/memory>
#include <string>
#include <set>
#include <tr1/unordered_map>

#include "DataSourceModule.hpp"
#include "SignalContainer.hpp"
#include "DataSourceException.hpp"

typedef std::tr1::shared_ptr<const DataSourceModule> ModulePtr;
typedef std::tr1::unordered_map<std::string,ModulePtr > FromName2Module;
typedef std::tr1::unordered_map<std::string,std::string> FromSignal2Module;
typedef std::tr1::unordered_map<std::string,std::set<std::string> > DependantModules;
typedef std::tr1::unordered_map<std::string,bool > UpdateState;


void append(DependantModules& map, const std::string& key, const std::string& value);

/** \author cec
 *  \brief Simplifies the creation of simulators using forward/reverse chaining.
 *  \details It provides modules with the data they need (which may come from other modules)
 *  \ingroup data_source
 *  \section ex1 Example
 *  \snippet data_source/unit_tests/src/DataSourceTest.cpp DataSourceTest example
 *  \section ex2 Expected output
 *  \snippet data_source/unit_tests/src/DataSourceTest.cpp DataSourceTest expected output
 */
class DataSource
{
    public:
        DataSource();
        DataSource(const DataSource& ds);

        /** \author cec
         *  \date 1 juil. 2013, 17:41:30
         *  \brief draws the DataSource's dependency graph
         *  \returns String containing the serialization of the DataSource
         *  \snippet data_source/unit_tests/src/DataSourceTest.cpp DataSourceTest draw_example
        */
        std::string draw() const;

        /** \author cec
         *  \date 17 juin 2013, 10:52:20
         *  \brief Adds a module to the DataSource.
         *  \details This method adds the module to the list, initializes it &
         *  retrieves all its dependencies.
         *  Another API which was considered earlier was add<M>(module_name) but
         *  this doesn't play well with mocks (you don't have access to
         *  the module because you leave its instantiation to the DataSource)
         *  \returns
         *  \snippet data_source/unit_tests/src/DataSourceTest.cpp DataSourceTest enclosing_method_example
        */
        void add(const DataSourceModule& module)
        {
            const ModulePtr m = add_module_if_not_already_present_and_return_clone(module);
            m->initialize();
            const bool read_only_bak = readonly;
            const std::string module_requesting_signals_bak = module_requesting_signals;
            const std::string module_setting_signals_bak = module_setting_signals;
            readonly = true; // We don't want the following call to module.update()
                              // to modify the signals in the DataSource: we just
                              // want to track module dependencies
            try
            {
                module_requesting_signals = m->get_name();
                m->update();
                module_requesting_signals = module_requesting_signals_bak;
                module_setting_signals = module_setting_signals_bak;
            }
            catch(DataSourceException& e)
            {
                throw(e);
            }
            catch(...)
            {
                // It's OK for m->update() to throw at this stage because we just want to retrieve its dependencies
            }
            //module_setting_signals = module_setting_signals_bak;
            readonly = read_only_bak;
        }

        void alias(const std::string& name_of_copy, const std::string& copied_signal);

        /** \author cec
         *  \date 24 juil. 2013, 15:13:58
         *  \brief Remove a module from a data source (and from the lists of dependencies)
         *  In this version, the module name is assumed to have been auto-generated.
         *  \returns Nothing
         *  \snippet data_source/unit_tests/src/DataSourceTest.cpp DataSourceTest enclosing_method_example
        */
        template <typename T> void remove()
        {
            const std::string module_to_remove = std::string(typeid(T).name()) + "auto-generated by DataSource";
            remove<T>(module_to_remove);
        }

        /** \author cec
         *  \date 24 juil. 2013, 15:13:58
         *  \brief Remove a module from a data source (and from the lists of dependencies)
         *  \returns Nothing
         *  \snippet data_source/unit_tests/src/DataSourceTest.cpp DataSourceTest enclosing_method_example
        */
        template <typename T> void remove(const std::string& module_to_remove)
        {
            if (name2module.find(module_to_remove) == name2module.end())
            {
                THROW(__PRETTY_FUNCTION__, DataSourceException,
                        std::string("Attempting to remove moduel '")
                                + module_to_remove
                                + "' which is not in this DataSource.");
            }
            module2dependantmodules.erase(module_to_remove);
            name2module.erase(module_to_remove);
            std::vector<std::string> signals_to_remove;
            for (FromSignal2Module::const_iterator it = signal2module.begin() ; it != signal2module.end() ; ++it)
            {
                if (it->second == module_to_remove) signals_to_remove.push_back(it->first);
            }
            for (std::vector<std::string>::const_iterator it = signals_to_remove.begin() ; it != signals_to_remove.end() ; ++it)
            {
                signal2module.erase(*it);
            }
            module2dependantmodules.erase(module_to_remove);
            module2requiredmodules.erase(module_to_remove);
            module2requiredsignals.erase(module_to_remove);
            update_dependencies();
        }

        /** \author cec
         *  \date 18 juin 2013, 22:19:54
         *  \brief Templated version of 'add'
         *  \details This is the version normally used to add a module because
         *  it automatically adds the present DataSource (*this) to the module's
         *  constructor.
         *  \returns Nothing
         *  \snippet data_source/unit_tests/src/DataSourceTest.cpp DataSourceTest enclosing_method_example
        */
        template <typename T> void add(const std::string& module_name)
        {
            if (module_name == "")
            {
                THROW(__PRETTY_FUNCTION__, DataSourceException, "Module name cannot be empty");
            }
            const T t(this, module_name);
            add(t);
        }

        /** \author cec
         *  \date 2 juil. 2013, 14:16:50
         *  \brief 'add' without specifying the name of the module (if there is only one of each type)
         *  \returns Nothing
         *  \snippet /unit_tests/src/DataSourceTest.cpp DataSourceTest enclosing_method_example
        */
        template <typename T> void add()
        {
            add<T>(std::string(typeid(T).name()) + "auto-generated by DataSource");
        }

        /** \author cec
         *  \date 17 juin 2013, 10:55:37
         *  \brief Retrieve the list of all modules currently in the DataSource
         *  \returns List of all present modules
         *  \snippet data_source/unit_tests/src/DataSourceTest.cpp DataSourceTest enclosing_method_example
        */
        FromName2Module get_modules() const;

        /** \author cec
         *  \date 17 juin 2013, 10:41:56
         *  \brief Removes all modules from a DataSource.
         *  \returns Nothing
         *  \snippet data_source/unit_tests/src/DataSourceTest.cpp DataSourceTest DataSource::clear_example
        */
        void clear();

        /** \author cec
         *  \date 18 juin 2013, 21:56:15
         *  \brief Adds/Updates a signal in the DataSource
         *  \returns Nothing
         *  \snippet data_source/unit_tests/src/DataSourceTest.cpp DataSourceTest set_example
        */
        template <typename T> void set(std::string signal_name, //<! Name of the signal to create or update
                                       const T& t)
        {
            std::map<std::string,std::string>::const_iterator it = aliases.find(signal_name);
            const bool found_alias = it != aliases.end();
            if (found_alias) signal_name = it->second;
            if (readonly)
            {
                std::tr1::unordered_map<std::string, std::string>::const_iterator it =
                        signal2module.find(signal_name + typeid(T).name());
                if ((it != signal2module.end()) && (it->second != "DataSource user" && (it->second != ""))
                        && (it->second != module_setting_signals))
                {
                    THROW(__PRETTY_FUNCTION__, DataSourceException,
                            std::string("Attempting to add module '")
                                    + module_setting_signals + "' which sets signal '"
                                    + signal_name + "', but module '"
                                    + it->second
                                    + "' already sets it: need to remove one of them using DataSource::remove.");
                }
                else if (signal_name != "")
                {
                    signal2module[signal_name + typeid(T).name()] =
                            module_setting_signals;
                    update_dependencies();
                }
            }
            else
            {
                signals_.set(signal_name + typeid(T).name(), t);
                DependantModules::const_iterator it = signal2dependantmodules
                        .find(signal_name + typeid(T).name());
                if (it != signal2dependantmodules.end())
                {
                    const std::set<std::string> S = it->second;
                    for (std::set<std::string>::const_iterator it = S.begin();
                            it != S.end(); ++it)
                    {
                        is_up_to_date[*it] = false;
                        const std::set<std::string> S2 =
                                module2dependantmodules[*it];
                        for (std::set<std::string>::const_iterator it2 = S2
                                .begin(); it2 != S2.end(); ++it2)
                        {
                            is_up_to_date[*it2] = false;
                        }
                    }
                }
            }
        }
private:
        void update_if_necessary(const std::string& module_name)
        {
            if (!(is_up_to_date[module_name]))
            {
                module_requesting_signals = module_name;
                name2module[module_name]->update();
            }
        }

        template<typename T>
        void append_to_maps(const std::string& signal_name)
        {
            append(signal2dependantmodules, signal_name + typeid(T).name(),
                    module_setting_signals);
            append(module2requiredsignals, module_setting_signals,
                    signal_name + typeid(T).name());
        }

        template<typename T>
        void update_or_throw(const std::string& signal_name)
        {
            const FromSignal2Module::const_iterator that_signal = signal2module
                    .find(signal_name + typeid(T).name());
            const bool computable = that_signal != signal2module.end();
            const bool stored = signals_.has < T
                    > (signal_name + typeid(T).name());
            if (computable)
            {
                const std::string module_name = that_signal->second;
                update_if_necessary(module_name);
            } else if (!(stored))
            {
                THROW(__PRETTY_FUNCTION__, DataSourceException,
                        std::string("Unable to find signal '") + signal_name
                                + "' required by module '"
                                + module_requesting_signals + "'");
            }
        }
public:
        /** \author cec
         *  \date 18 juin 2013, 22:01:33
         *  \brief Retrieves a signal from the SignalContainer
         *  \returns Value of the signal
         *  \snippet data_source/unit_tests/src/DataSourceTest.cpp DataSourceTest get_example
         */
        template<typename T>
        T get(const std::string& signal_name)
        {
            std::map<std::string,std::string>::const_iterator it = aliases.find(signal_name);
            if (it != aliases.end())
            {
                return get<T>(it->second);
            }
            if (readonly && (module_setting_signals != "DataSource user"))
            {
                append_to_maps<T>(signal_name);
                const std::string module_requesting_signals_bak = module_requesting_signals;
                const std::string module_setting_signals_bak = module_setting_signals;
                update_dependencies();
                module_requesting_signals = module_requesting_signals_bak;
                module_setting_signals = module_setting_signals_bak;
                return T();
            }
            else
            {
                const std::string module_requesting_signals_bak = module_requesting_signals;
                const std::string module_setting_signals_bak = module_setting_signals;
                update_or_throw<T>(signal_name);
                module_requesting_signals = module_requesting_signals_bak;
                module_setting_signals = module_setting_signals_bak;
            }
            return signals_.get<T>(signal_name + typeid(T).name());
        }
        bool read_only() const;
        void define_derivative(const std::string& state_name, const std::string& derivative_name);
        void get_derivatives(std::vector<double>& dx_dt);
        void set_states(const std::vector<double>& v);
        std::vector<std::string> get_state_names() const;
        std::vector<std::string> get_all_signal_names() const;

    private:
        ModulePtr add_module_if_not_already_present_and_return_clone(const DataSourceModule& module);
        std::set<std::string> get_dependencies(const std::string& module_name, std::set<std::string>& ret) const;
        std::set<std::string> get_dependencies(const std::string& ref_module, const std::string& current_module, std::set<std::string>& dependencies) const;
        bool a_module_depends_on_itself();
        void update_dependencies();
        void add_dependencies_and_dependent_modules(const std::set<std::string>& required_signals, const std::string& module_using_required_signals);
        FromName2Module name2module; //!< Map giving, for each module name, a (smart) pointer to the corresponding module
        bool readonly; //!< If this flag is set to true, DataSource::set will not modify the state of the DataSource. This is used so that the first call to DataSourceModule::update (by DataSource::add) can track dependencies between modules
        SignalContainer signals_; //!< All signals currently in the DataSource
        std::string module_setting_signals; //!< Module currently adding signals to the DataSource (used to track if two different modules set the same signal)
        std::string module_requesting_signals; //!< Module currently getting signals from the DataSource (used to track which module is requiring a missing signal)
        FromSignal2Module signal2module; //!< Tracks which module sets which signal
        DependantModules module2dependantmodules; //!< For each module, stores the set of the names of the modules depending on it
        DependantModules module2requiredmodules; //!< For each module, stores the set of the names of the modules it depends on
        DependantModules module2requiredsignals; //!< For each module, stores the signals it depends on
        DependantModules signal2dependantmodules; //!< For each signal, stores the modules that depend on it
        UpdateState is_up_to_date; //!< For each module, whether it is up-to-date or not
        std::vector<std::pair<std::string,std::string> > state_names;
        std::map<std::string,std::string> aliases;
};



#endif /* DATASOURCE_HPP_ */
