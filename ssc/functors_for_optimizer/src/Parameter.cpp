#include "Parameter.hpp"


Parameter::~Parameter()
{
}

ValType Parameter::val() const
{
    return lambda*f;
}

Grad Parameter::grad() const
{
    return Grad();
}

Hes Parameter::hes() const
{
    return Hes();
}

Parameter::Parameter(const double& v) :
        ptr(SharedPtr(new double(v))),
        df(Grad()),
        d2f(Hes()),
        f([&ptr]()->double{return *ptr;})
{
}

bool Parameter::operator==(const Parameter& rhs) const
{
    return ptr==rhs.ptr;
}

bool Parameter::operator!=(const Parameter& rhs) const
{
    return not(*this==rhs); 
}

double& operator*(const Parameter& s)
{
    return *s.ptr;
}

