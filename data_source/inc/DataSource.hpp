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
#include "DataSourceModule.hpp"

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
         *  \snippet /unit_tests/src/DataSourceTest.cpp DataSourceTest enclosing_method_example
        */
        template <class T> void add(const T& module)
        {
            const ModulePtr m = add_module_if_not_already_present(module.clone());
            m->initialize();
            const bool read_only_bak = read_only;
            read_only = true; // We don't want the following call to module.update()
                              // to modify the signals in the DataSource: we just
                              // want to track module dependencies
            m->update();
            read_only = read_only_bak;
        }

        /** \author cec
         *  \date 17 juin 2013, 10:55:37
         *  \brief Retrieve the list of all modules currently in the DataSource
         *  \returns List of all present modules
         *  \snippet /unit_tests/src/DataSourceTest.cpp DataSourceTest enclosing_method_example
        */
        FromName2Module get_modules() const;

        /** \author cec
         *  \date 17 juin 2013, 10:41:56
         *  \brief Removes all modules from a DataSource.
         *  \returns Nothing
         *  \snippet /unit_tests/src/DataSourceTest.cpp DataSourceTest DataSource::clear_example
        */
        void clear();

    private:
        /** \author cec
         *  \date 17 juin 2013, 11:00:13
         *  \details Checks if a module with the same name exists in the DataSource.
         *  If it exists, throw an exception. Otherwise, add the module to name2module.
         *  \returns Pointer to the added module.
         *  \snippet /unit_tests/src/DataSourceTest.cpp DataSourceTest enclosing_method_example
        */
        ModulePtr add_module_if_not_already_present(DataSourceModule const * const module //<! Module to add
                                              );

        FromName2Module name2module;
        bool read_only;
};

#endif /* DATASOURCE_HPP_ */
