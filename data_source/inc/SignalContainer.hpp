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


class SignalContainerException : public Exception
{
    public:
        SignalContainerException(const char* s) :
                Exception(s)
        {
        }
};

typedef std::string SignalName;
typedef std::string TypeName;



/** \author cec
 * \ingroup data_source
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
    private:
        class TypedSignalName
        {
            public:
                TypedSignalName(const SignalName& signal_name, const TypeName& type_name);
                bool operator<(const TypedSignalName& rhs) const;
                SignalName get_signal_name() const;
                TypeName get_type_name() const;
            private:
                TypedSignalName();
                SignalName _signal_name;
                TypeName _type_name;

        };
        typedef std::map<TypedSignalName, boost::any> Signals;
        typedef Signals::const_iterator ConstSignalIterator;
    public:
        SignalContainer();
        template <typename T> void set(const std::string& signal_name, const T& value)
        {
            signals[TypedSignalName(signal_name,typeid(T).name())] = value;
        }

        template <typename T> T get(const std::string& signal_name) const
        {
            const TypedSignalName name(signal_name,typeid(T).name());
            ConstSignalIterator it = signals.find(name);
            if (it == signals.end())
            {
                std::string msg = "unable to find a signal named '";
                msg += name.get_signal_name();
                msg += "' of type '" + name.get_type_name() + "'";
                const std::string function_name = std::string(typeid(T).name()) + " SignalContainer::get(const std::string& signal_name) const";
                THROW(function_name, SignalContainerException, msg);
            }
            return boost::any_cast<T>(it->second);
        }

        template <class T> typename std::map<SignalName, T> get_all() const
        {
            std::map<SignalName, T> ret;
            for (ConstSignalIterator it = signals.begin() ; it != signals.end() ; ++it)
            {
                if (it->first.get_type_name() == typeid(T).name())
                {
                    ret.insert(std::make_pair(it->first.get_signal_name(),boost::any_cast<T>(it->second)));
                }
            }
            return ret;
        }


    private:
        Signals signals;
};

#endif /* SIGNALCONTAINER_HPP_ */
