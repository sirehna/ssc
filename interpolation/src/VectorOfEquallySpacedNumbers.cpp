/*
 * VectorOfEquallySpacedNumbers.cpp
 *
 * \date 31 juil. 2012, 09:06:33
 *  \author cec
 */

#include "VectorOfEquallySpacedNumbers.hpp"
#include "test_macros.hpp"
#include <sstream>

VectorOfEquallySpacedNumbers::VectorOfEquallySpacedNumbers(const double& min_bound, const double& max_bound, const size_t& nb_of_values) :
_min_bound(min_bound),
_max_bound(max_bound),
_nb_of_values(nb_of_values),
vec(std::vector<double>()),
delta((_max_bound-_min_bound)/double(_nb_of_values-1))
{
	if (_min_bound>_max_bound)
	{
	    std::stringstream msg;
	    msg << "_min_bound = " << _min_bound
	        << ", _max_bound = " << _max_bound;
		THROW("VectorOfEquallySpacedNumbers::VectorOfEquallySpacedNumbers(const double&, const double&, const size_t&)", VectorOfEquallySpacedNumbersException, msg.str());
	}
	if (_nb_of_values<1)
	{
		THROW("VectorOfEquallySpacedNumbers::VectorOfEquallySpacedNumbers(const double&, const double&, const size_t&)", VectorOfEquallySpacedNumbersException, "need at least two values in VectorOfEquallySpacedNumbers");
	}
	if (_nb_of_values>vec.max_size())
	{
		THROW("VectorOfEquallySpacedNumbers::VectorOfEquallySpacedNumbers(const double&, const double&, const size_t&)", VectorOfEquallySpacedNumbersException, "too many elements");
	}
	vec.reserve(_nb_of_values);
	if (_nb_of_values>1)
	{
        for (size_t i = 0 ; i < _nb_of_values ; ++i)
        {
            vec.push_back(_min_bound*(_nb_of_values-1)+i*(_max_bound-_min_bound));
            vec.back() /= double(_nb_of_values-1);
        }
	}
	else
	{
	    if (min_bound!=max_bound)
	    {
	        THROW("VectorOfEquallySpacedNumbers::VectorOfEquallySpacedNumbers(const double&, const double&, const size_t&)", VectorOfEquallySpacedNumbersException, "If there is only one value, min & max need to be equal");
	    }
	    vec.push_back(min_bound);
	}
}

std::vector<double> VectorOfEquallySpacedNumbers::get() const
{
	return vec;
}

double VectorOfEquallySpacedNumbers::get_delta() const
{
	return delta;
}

size_t VectorOfEquallySpacedNumbers::size() const
{
	return _nb_of_values;
}

double VectorOfEquallySpacedNumbers::get_min() const
{
	return _min_bound;
}

double VectorOfEquallySpacedNumbers::get_max() const
{
	return _max_bound;
}

double VectorOfEquallySpacedNumbers::at(const size_t& i) const
{
    if (_nb_of_values==1) return vec.back();
	if (i>=_nb_of_values)
	{
		THROW("VectorOfEquallySpacedNumbers::VectorOfEquallySpacedNumbers::at(const size_t&)", VectorOfEquallySpacedNumbersException, "Index out of range");
	}
	return (_min_bound*(_nb_of_values-1)+i*(_max_bound-_min_bound))/double(_nb_of_values-1);
}
