#include "Parameter.hpp"
#include "NodeAbstractVisitor.hpp"
#include <sstream>

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

void Parameter::accept(NodeAbstractVisitor& v) const
{
    v.visit(*this);
}

Node* Parameter::clone() const
{
    return new Parameter(*this);
}

std::string Parameter::get_address_string() const
{
    std::stringstream ss;
    ss << ptr.get();
    return ss.str();
}
