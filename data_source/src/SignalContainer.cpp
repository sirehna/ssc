/*
 * SignalContainer.cpp
 *
 * \date 18 mars 2013, 17:52:42
 *  \author cec
 */

#include "SignalContainer.hpp"
#include <boost/any.hpp>
#include <algorithm>

SignalContainer::SignalContainer() : signals(Signals()), scalar_convertible_types(ConvertibleTypes()),
vector_convertible_types(ConvertibleTypes())
{

}


double get_key(const std::pair<SignalName, double>& kv);
double get_key(const std::pair<SignalName, double>& kv)
{
    return kv.second;
}

std::vector<double> SignalContainer::to_doubles() const
{
    const std::map<SignalName, double> s = get_all<double>();
    std::vector<double> ret(s.size(),0);
    std::transform(s.begin(), s.end(), ret.begin(), get_key);
    return ret;
}
