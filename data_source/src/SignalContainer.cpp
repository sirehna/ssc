/*
 * SignalContainer.cpp
 *
 * \date 18 mars 2013, 17:52:42
 *  \author cec
 */

#include "SignalContainer.hpp"
#include <boost/any.hpp>

SignalContainer::SignalContainer() : signals(Signals())
{

}

SignalContainer::TypedSignalName::TypedSignalName(const SignalName& signal_name, const TypeName& type_name) : _signal_name(signal_name),
                    _type_name(type_name)
{}

bool SignalContainer::TypedSignalName::operator<(const TypedSignalName& rhs) const
{
    const bool is_lower =  ((_signal_name < rhs._signal_name)
                           || ((_signal_name == rhs._signal_name) && (_type_name < rhs._type_name)));
    return is_lower;
}

SignalName SignalContainer::TypedSignalName::get_signal_name() const
{
    return _signal_name;
}
TypeName SignalContainer::TypedSignalName::get_type_name() const
{
    return _type_name;
}
