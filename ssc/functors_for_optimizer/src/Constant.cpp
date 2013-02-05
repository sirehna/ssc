/*
 * Constant.cpp
 *
 * \date 29 janv. 2013, 09:41:02
 *  \author cec
 */

#include "Constant.hpp"
#include "Null.hpp"
#include "State.hpp"
#include "NodeVisitor.hpp"

Parameter::Parameter(const double& val) : ptr(new double(val))
{
    set_value([ptr,&lambda]()->double {return lambda*(*ptr);});
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
