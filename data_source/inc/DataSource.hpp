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

/** \author cec
 *  \brief This class was created to simplify the creation of simulators.
 *  \details Its responsibility is to provide models with the data they need (which may come from other models)
 *  \section ex1 Example
 *  \snippet data_source/unit_tests/src/DataSourceTest.cpp DataSourceTest example
 *  \section ex2 Expected output
 *  \snippet data_source/unit_tests/src/DataSourceTest.cpp DataSourceTest expected output
 */

typedef std::tr1::shared_ptr<DataSourceModule> ModulePtr;
typedef std::map<std::string,ModulePtr > FromName2Module;

class DataSource
{
    public:
        DataSource();
        template <class T> void add(const T& module)
        {
            name2module[module.get_name()] = module.clone();
        }

        FromName2Module get_modules() const;
        void clear();

    private:
        FromName2Module name2module;
};

#endif /* DATASOURCE_HPP_ */
