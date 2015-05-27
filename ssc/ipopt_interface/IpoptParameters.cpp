/*
 * IpoptParameters.cpp
 *
 * \date 26 f�vr. 2013, 10:31:33
 *  \author cec
 */

#include "ssc/ipopt_interface/IpoptParameters.hpp"


PositiveDouble::PositiveDouble(const double& val) : value(val)
{
    if (value<0)
    {
        THROW("PositiveDouble::PositiveDouble(const double&)", PositiveDoubleException, "negative double");
    }
}

PositiveDouble::operator double() const
{
    return value;
}

double PositiveDouble::operator+(const double& rhs) const
{
    return value+rhs;
}

PositiveDouble PositiveDouble::operator+(const PositiveDouble& rhs) const
{
    return PositiveDouble(value+rhs.value);
}

double PositiveDouble::operator-(const double& rhs) const
{
    return value-rhs;
}

double PositiveDouble::operator-(const PositiveDouble& rhs) const
{
    return value-rhs.value;
}

PositiveDouble PositiveDouble::operator*(const PositiveDouble& rhs) const
{
    return PositiveDouble(value*rhs.value);
}

double PositiveDouble::operator*(const double& rhs) const
{
    return value*rhs;
}

PositiveDouble PositiveDouble::operator/(const PositiveDouble& rhs) const
{
    return PositiveDouble(value/rhs.value);
}

double PositiveDouble::operator/(const double& rhs) const
{
    return value/rhs;
}
PositiveDouble& PositiveDouble::operator=(const PositiveDouble& rhs)
{
    if (&rhs != this)
    {
        value = rhs.value;
    }
    return *this;
}

double operator+(const double& lhs, const PositiveDouble& rhs)
{
    return rhs+lhs;
}

double operator-(const double& lhs, const PositiveDouble& rhs)
{
    return -(rhs-lhs);
}

double operator*(const double& lhs, const PositiveDouble& rhs)
{
    return rhs*lhs;
}

double operator/(const double& lhs, const PositiveDouble& rhs)
{
    return rhs/lhs;
}


IpoptParameters::IpoptParameters() : tolerance(1e-9),
                                     bound_relaxation_factor(0),
                                     mu_strategy("adaptive"),
                                     print_level(0),
                                     maximum_number_of_iterations(1000),
                                     trace_function_calls(false),
                                     show_evaluated_points(false),
                                     check_first_derivative(false),
                                     check_second_derivative(false)
{
}

