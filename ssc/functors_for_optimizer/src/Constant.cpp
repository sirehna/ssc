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

Constant::Constant(const double& val) : ptr(new double(val))
{
    set_value([ptr,&lambda]()->double {return lambda*(*ptr);});
}

NodePtr Constant::diff(const StatePtr& state) const
{
    if (state->get_index())
    {

    }
    return NodePtr(new Null);
}

bool Constant::operator==(const Constant& rhs) const
{
    return ptr==rhs.ptr;
}

bool Constant::operator!=(const Constant& rhs) const
{
    return not(*this==rhs);
}

double& operator*(const Constant& s)
{
    return *s.ptr;
}

void Constant::accept(NodeVisitor& v) const
{
    v.visit(*this);
}
