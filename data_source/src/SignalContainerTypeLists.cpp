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
iter_short(std::list<ConstSignalIterator>()),
iter_int(std::list<ConstSignalIterator>()),
iter_size_t(std::list<ConstSignalIterator>()),
iter_long(std::list<ConstSignalIterator>()),
iter_float(std::list<ConstSignalIterator>()),
iter_double(std::list<ConstSignalIterator>()),
iter_phys_qty(std::list<ConstSignalIterator>()),
bin(std::list<ConstSignalIterator>())
{

}

void ConvertibleTypes::clear()
{
    iter_bool.clear();
    iter_char.clear();
    iter_wchar_t.clear();
    iter_short.clear();
    iter_int.clear();
    iter_size_t.clear();
    iter_long.clear();
    iter_float.clear();
    iter_double.clear();
    iter_phys_qty.clear();
    bin.clear();
}

template<> std::list<ConstSignalIterator>& select_list_from_type<bool>(ConvertibleTypes& lists)
{
    return lists.iter_bool;
}

template<> std::list<ConstSignalIterator>& select_list_from_type<char>(ConvertibleTypes& lists)
{
    return lists.iter_char;
}

template<> std::list<ConstSignalIterator>& select_list_from_type<wchar_t>(ConvertibleTypes& lists)
{
    return lists.iter_wchar_t;
}
template<> std::list<ConstSignalIterator>& select_list_from_type<short>(ConvertibleTypes& lists)
{
    return lists.iter_short;
}

template<> std::list<ConstSignalIterator>& select_list_from_type<int>(ConvertibleTypes& lists)
{
    return lists.iter_int;
}

template<> std::list<ConstSignalIterator>& select_list_from_type<size_t>(ConvertibleTypes& lists)
{
    return lists.iter_size_t;
}

template<> std::list<ConstSignalIterator>& select_list_from_type<long>(ConvertibleTypes& lists)
{
    return lists.iter_long;
}

template<> std::list<ConstSignalIterator>& select_list_from_type<float>(ConvertibleTypes& lists)
{
    return lists.iter_float;
}

template<> std::list<ConstSignalIterator>& select_list_from_type<double>(ConvertibleTypes& lists)
{
    return lists.iter_double;
}

template<> std::list<ConstSignalIterator>& select_list_from_type<PhysicalQuantity>(ConvertibleTypes& lists)
{
    return lists.iter_phys_qty;
}





DEFINE_TYPE_ACCESSORS(bool)
DEFINE_TYPE_ACCESSORS(char)
DEFINE_TYPE_ACCESSORS(wchar_t)
DEFINE_TYPE_ACCESSORS(short)
DEFINE_TYPE_ACCESSORS(int)
DEFINE_TYPE_ACCESSORS(size_t)
DEFINE_TYPE_ACCESSORS(long)
DEFINE_TYPE_ACCESSORS(float)
DEFINE_TYPE_ACCESSORS(double)
template <> ConvertibleTypesIterator begin<PhysicalQuantity>(const ConvertibleTypes& l)
{
    return l.iter_phys_qty.begin();
}

template <> ConvertibleTypesIterator end<PhysicalQuantity>(const ConvertibleTypes& l)
{
    return l.iter_phys_qty.end();
}
