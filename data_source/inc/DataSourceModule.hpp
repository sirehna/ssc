/*
 * Model.hpp
 *
 * \date 15 mars 2013, 11:21:25
 *  \author cec
 */

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <tr1/memory>
#include <string>

class DataSource;

/** \author cec
 *  \brief Generic API for a module usable by the DataSource.
 *  \details The primary responsibility of any module is to compute its outputs
 *  from its inputs (which are given by DataSource). As it does not maintain its
 *  states, all of its methods are const. If you add states to a class deriving
 *  from DataSourceModule, there is no guarantee that the simulation will be
 *  repeatable.
 *  \ingroup data_source
 *  \section ex1 Example
 *  \snippet data_source/unit_tests/src/DataSourceModuleTest.cpp DataSourceModuleTest example
 *  \section ex2 Expected output
 *  \snippet data_source/unit_tests/src/DataSourceModuleTest.cpp DataSourceModuleTest expected output
 */
class DataSourceModule
{
    public:
        DataSourceModule(DataSource* const data_source, const std::string& module_name);
        virtual ~DataSourceModule();

        /** \author cec
         *  \date 17 juin 2013, 10:20:19
         *  \brief Clones the current module
         *  \details This method is called by the DataSource when adding a
         *  module so we can have a container with pointers to each module.
         *  \returns Typically, std::tr1::shared_ptr<DataSourceModule>(new DataSourceModule(*this));
         *  \snippet /unit_tests/src/DataSourceModuleTest.cpp DataSourceModuleTest enclosing_method_example
        */
        virtual DataSourceModule* clone() const = 0;

        /** \author cec
         *  \date 17 juin 2013, 09:41:57
         *  \brief Sets all output signals of the module.
         *  \details This method is used by the DataSource:
         *  - When adding a module (so the DataSource can build the forward/
         *  reverse-dependency chain), in which case the DataSource sets itself
         *  to "read only" mode.
         *  - When querying a value computed by that module
         *  \returns Nothing
         *  \snippet /unit_tests/src/DataSourceModuleTest.cpp DataSourceModuleTest enclosing_method_example
        */
        virtual void update() const = 0;

        /** \author cec
         *  \date 17 juin 2013, 09:55:46
         *  \brief Returns the *module* name (not the *system* name)
         *  \details This method is only virtual so that it may be tracked by
         *  mocks but the default implementation should suffice in most cases.
         *  \returns Name of the module.
         *  \snippet /unit_tests/src/DataSourceModuleTest.cpp DataSourceModuleTest enclosing_method_example
        */
        virtual std::string get_name() const;

        /** \author cec
         *  \date 17 juin 2013, 10:07:45
         *  \brief Populates the emitting DataSource with the module's states
         *  \details This method is systematically called when adding a module
         *  to a DataSource. By default it doesn't do anything (and therefore
         *  only needs to be overriden for "statefull" modules).
         *  \returns Nothing
         *  \snippet /unit_tests/src/DataSourceModuleTest.cpp DataSourceModuleTest enclosing_method_example
        */
        virtual void initialize() const;

        DataSourceModule(const DataSourceModule& rhs) : ds(rhs.ds), module_name_(rhs.module_name_)
        {

        }

        DataSourceModule& operator=(const DataSourceModule& rhs)
        {
            if (&rhs != this)
            {
                ds = rhs.ds;
                module_name_ = rhs.module_name_;
            }
            return *this;
        }


    protected:
        DataSource* ds;

    private:
        DataSourceModule(); // Disabled by making it private & with no implementation
        std::string module_name_;
};

// This macro is meant to simplify the creation of modules: only the update() method needs to be defined to have a functional module
#define DECLARE_MODULE(module_name) class module_name : public DataSourceModule\
                                    {\
                                        public:\
                                            module_name(DataSource* const data_source, const std::string& module_name) : DataSourceModule(data_source, module_name)\
                                            {\
                                            }\
                                    \
                                            DataSourceModule* clone() const\
                                            {\
                                                return new module_name(*this);\
                                            }\
                                    \
                                            void update() const;\
                                    };


#endif /* MODEL_HPP_ */
