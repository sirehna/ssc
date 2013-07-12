/*
 * SignalContainer.cpp
 *
 * \date 18 mars 2013, 17:52:42
 *  \author cec
 */

#include "SignalContainer.hpp"
#include "TypeCoercion.hpp"
#include "PhysicalQuantity.hpp"

SignalContainer::SignalContainer() : signals(Signals()), scalar_convertible_types(ConvertibleTypes()),
vector_convertible_types(ConvertibleTypes())
{

}


template <> void SignalContainer::coerce_type<PhysicalQuantity>(std::list<double>& ret) const
{
for (ConvertibleTypesIterator it  = scalar_convertible_types.iter_phys_qty.begin() ; it != scalar_convertible_types.iter_phys_qty.end() ; ++it)
    {
        boost::any_cast<PhysicalQuantity>((*it)->second).coerce(ret);
    }
    for (ConvertibleTypesIterator it  = vector_convertible_types.iter_phys_qty.begin() ; it != vector_convertible_types.iter_phys_qty.end() ; ++it)
    {
        std::vector<PhysicalQuantity> v = boost::any_cast<std::vector<PhysicalQuantity> >((*it)->second);
        for (std::vector<PhysicalQuantity>::const_iterator i = v.begin() ; i != v.end() ; ++i)
        {
            i->coerce(ret);
        }
    }
}

std::list<double> SignalContainer::to_doubles() const
{
    std::list<double> ret;

    coerce_type<bool>(ret);
    coerce_type<char>(ret);
    coerce_type<wchar_t>(ret);
    coerce_type<short>(ret);
    coerce_type<int>(ret);
    coerce_type<size_t>(ret);
    coerce_type<long>(ret);
    coerce_type<float>(ret);
    coerce_type<double>(ret);
    coerce_type<PhysicalQuantity>(ret);

    return ret;
}
