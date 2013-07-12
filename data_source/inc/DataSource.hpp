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
#include <map>
#include <tr1/unordered_map>

#include "DataSourceModule.hpp"
#include "SignalContainer.hpp"
#include "DataSourceException.hpp"
#include "test_macros.hpp"

typedef std::tr1::shared_ptr<const DataSourceModule> ModulePtr;
typedef std::map<std::string,ModulePtr > FromName2Module;

/** \author cec
 *  \brief Simplifies the creation of simulators using forward/reverse chaining.
 *  \details It provides models with the data they need (which may come from other models)
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
            const ModulePtr m = add_module_if_not_already_present_and_return_clone(module.clone());
            m->initialize();
            const bool read_only_bak = read_only;
            read_only = true; // We don't want the following call to module.update()
                              // to modify the signals in the DataSource: we just
                              // want to track module dependencies
            m->update();
            current_module = "";
            read_only = read_only_bak;
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
            const T t(this, module_name);
            add(t);
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
        template <typename T> void set(const std::string& signal_name, //<! Name of the signal to create or update
                                       const T& t //<! Value to add to DataSource
                                       )
        {
            if (read_only)
            {
                std::tr1::unordered_map<std::string,std::string>::const_iterator it = signal2module.find(signal_name);
                if ((it != signal2module.end()) && (it->second != "") && (it->second != current_module))
                {
                    THROW(__PRETTY_FUNCTION__, DataSourceException, std::string("Attempting to add module '") + current_module + "' which sets signal '"
                                                                    + signal_name + "', but module '" + it->second + "' already sets it: need to remove one of them using DataSource::remove.");
                }
                else
                {
                    signal2module[signal_name] = current_module;
                }
            }
            else
            {
                signals.set(signal_name,t);
            }
        }

        /** \author cec
         *  \date 18 juin 2013, 22:01:33
         *  \brief Retrieves a signal from the SignalContainer
         *  \returns Value of the signal
         *  \snippet data_source/unit_tests/src/DataSourceTest.cpp DataSourceTest get_example
        */
        template <typename T> T get(const std::string& signal_name //<! Name of the signal to create or update
                                    ) const
        {
            T ret;
            try
            {
                ret = signals.get<T>(signal_name);
            }
            catch(Exception& e)
            {
                if (not(read_only)) // When a module is added, it is quite possible
                                    // that all its dependencies are not available:
                                    // we only throw if we're past the module addition
                {
                    THROW(__PRETTY_FUNCTION__, DataSourceException, std::string("exception caught: ") + e.what());
                }
            }
            return ret;
        }


    private:
        /** \author cec
         *  \date 17 juin 2013, 11:00:13
         *  \details Checks if a module with the same name exists in the DataSource.
         *  If it exists, throw an exception. Otherwise, add the module to name2module.
         *  \returns Pointer to the added module.
         *  \snippet /unit_tests/src/DataSourceTest.cpp DataSourceTest enclosing_method_example
        */
        ModulePtr add_module_if_not_already_present_and_return_clone(DataSourceModule const * const module //<! Module to add
                                              );

        FromName2Module name2module;
        bool read_only;
        SignalContainer signals;
        std::string current_module; //<! Module currently adding signals to the DataSource (used to track if two different modules set the same signal)
        std::tr1::unordered_map<std::string,std::string> signal2module; //!< Used to track if two different modules set the same signal
};

#endif /* DATASOURCE_HPP_ */
