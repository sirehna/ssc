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

class DataSourceModule
{
    public:
        DataSourceModule(const std::tr1::shared_ptr<DataSource>& data_source, const std::string& module_name);
        virtual ~DataSourceModule();
        virtual std::tr1::shared_ptr<DataSourceModule> clone() const = 0;
        virtual void set_all(const bool& read_only=true) = 0;
        virtual std::string get_name() const;

    protected:
        DataSourceModule();
        std::tr1::shared_ptr<DataSource> ds;

    private:
        std::string module_name_;
};


#endif /* MODEL_HPP_ */
