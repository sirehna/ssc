/*
 * Constant.cpp
 *
 * \date 29 janv. 2013, 09:41:02
 *  \author cec
 */

#include "Parameter.hpp"
#include "Null.hpp"
#include "State.hpp"
#include "NodeVisitor.hpp"

Parameter::Parameter() : ptr(new double(0))
{
    set_value([ptr,factor]()->double {return factor*(*ptr);});
}

Parameter::Parameter(const double& val) : ptr(new double(val))
{
    set_value([ptr,factor]()->double {return factor*(*ptr);});
}

NodePtr Parameter::diff(const StatePtr& state) const
{
    if (state->get_index())
    {

    }
    return NodePtr(new Null);
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

void Parameter::accept(NodeVisitor& v) const
{
    v.visit(*this);
}

NodePtr Parameter::clone() const
{
    return NodePtr(new Parameter(*this));
}

bool Parameter::is_null() const
{
    return *ptr==0;
}

bool Parameter::equals(const Node& rhs) const
{
    return rhs.equals_derived(*this);
}

bool Parameter::equals_derived(const Parameter& rhs) const
{
    return *ptr == *(rhs.ptr);
}

std::string Parameter::get_type() const
{
    return "Parameter";
}


