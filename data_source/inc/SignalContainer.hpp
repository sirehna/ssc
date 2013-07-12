/*
 * SignalContainer.hpp
 *
 * \date 18 mars 2013, 17:52:42
 *  \author cec
 */

#ifndef SIGNALCONTAINER_HPP_
#define SIGNALCONTAINER_HPP_

#include <boost/any.hpp>
#include <map>
#include <typeinfo>

#include "Exception.hpp"
#include "test_macros.hpp"

class SignalContainerException : public Exception
{
    public:
        SignalContainerException(const char* s) :
                Exception(s)
        {
        }
};


typedef std::string SignalName;
typedef std::string TypedSignalName;
typedef std::map<TypedSignalName, boost::any> Signals;
typedef Signals::const_iterator ConstSignalIterator;

/** \author cec
 *  \brief This class was created to store signals of different types using boost::any
 *  \details It has the following responsibilities:
 *  - Store & retrieve signals by name
 *  - Convert a list of signal names (or all of its signals) to a vector of
 *    doubles (for Euler & RK integration)
 *  - Accept a visitor for serialization (eg. to an output file)
 *  \section ex1 Example
 *  \snippet data_source/unit_tests/src/SignalContainerTest.cpp SignalContainerTest example
 *  \section ex2 Expected output
 *  \snippet data_source/unit_tests/src/SignalContainerTest.cpp SignalContainerTest expected output
 */

class SignalContainer
{
    public:
        SignalContainer();
        template <typename T> void add(const std::string& signal_name, const T& value)
        {
            signals[typeid(T).name()+signal_name] = value;
        }

        template <typename T> T get(const std::string& signal_name) const
        {
            T t;
            const TypedSignalName name = typeid(T).name()+signal_name;
            ConstSignalIterator it = signals.find(name);
            if (it == signals.end())
            {
                std::string msg = "unable to find '";
                msg += name;
                msg += "'";
                const std::string function_name = std::string(typeid(t).name()) + " SignalContainer::get(const std::string& signal_name) const";
                THROW(function_name, SignalContainerException, "unable to find signal");
            }
            return boost::any_cast<T>(it->second);
        }

    private:
        Signals signals;
};

#endif /* SIGNALCONTAINER_HPP_ */
