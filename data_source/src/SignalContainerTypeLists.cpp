/*
 * SignalContainerTypeLists.cpp
 *
 * \date 18 juin 2013, 10:42:29
 *  \author cec
 */

#include "SignalContainerTypeLists.hpp"

TypedSignalName::TypedSignalName(const SignalName& signal_name, const TypeName& type_name) : _signal_name(signal_name),
                    _type_name(type_name)
{}

bool TypedSignalName::operator<(const TypedSignalName& rhs) const
{
    const bool is_lower =  ((_signal_name < rhs._signal_name)
                           || ((_signal_name == rhs._signal_name) && (_type_name < rhs._type_name)));
    return is_lower;
}

bool TypedSignalName::operator==(const TypedSignalName& rhs) const
{
    return (_signal_name == rhs._signal_name) && (_type_name == rhs._type_name);
}

SignalName TypedSignalName::get_signal_name() const
{
    return _signal_name;
}
TypeName TypedSignalName::get_type_name() const
{
    return _type_name;
}


ConvertibleTypes::ConvertibleTypes() :
iter_bool(std::list<ConstSignalIterator>()),
iter_char(std::list<ConstSignalIterator>()),
iter_wchar_t(std::list<ConstSignalIterator>()),
iter_char16_t(std::list<ConstSignalIterator>()),
iter_char32_t(std::list<ConstSignalIterator>()),
iter_short(std::list<ConstSignalIterator>()),
iter_int(std::list<ConstSignalIterator>()),
iter_long(std::list<ConstSignalIterator>()),
iter_float(std::list<ConstSignalIterator>()),
iter_double(std::list<ConstSignalIterator>()),
iter_phys_qty(std::list<ConstSignalIterator>()),
bin(std::list<ConstSignalIterator>())
{

}

