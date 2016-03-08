/*
 * Constant.cpp
 *
 * \date 29 janv. 2013, 09:41:02
 *  \author cec
 */

#include "ssc/functors_for_optimizer/Parameter.hpp"
#include "ssc/functors_for_optimizer/Null.hpp"
#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"

using namespace ssc::functors_for_optimizer;

#if defined(_MSC_VER)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#define not !
#endif

Parameter::Parameter() : ptr(new double(0)), nb_of_copies(0), index(0)
{
    update_lambda();
}

void Parameter::update_lambda()
{
    const auto ptr_ = ptr;
    const auto factor_ = factor;
    set_value([ptr_,factor_]()->double {return factor_*(*ptr_);});
}

Parameter::Parameter(const double val, const size_t idx) : ptr(new double(val)), nb_of_copies(0), index(idx)
{
    update_lambda();
}

Parameter::Parameter(const double val) : ptr(new double(val)), nb_of_copies(0), index(0)
{
    update_lambda();
}

Parameter::~Parameter()
{
}

Parameter::Parameter(const Parameter& rhs) : Nullary(rhs.factor), ptr(rhs.ptr), nb_of_copies(rhs.nb_of_copies), index(rhs.index)
{
    nb_of_copies++;
    update_lambda();
}


Parameter& Parameter::operator=(const Parameter& rhs)
{
    if (&rhs != this)
    {
        ptr = rhs.ptr;
        factor = rhs.factor;
        nb_of_copies = rhs.nb_of_copies;
        index = rhs.index;
        update_lambda();
    }
    return *this;
}

Parameter& Parameter::operator=(const double rhs)
{
    *ptr = rhs;
    factor = 1;
    update_lambda();
    return *this;
}

NodePtr Parameter::diff(const StatePtr& state) const
{
    (void)state;
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

/*
double& operator*(const Parameter& s)
{
    return *s.ptr;
}*/

void Parameter::accept(NodeVisitor& v) const
{
    v.visit(*this);
}

NodePtr Parameter::clone() const
{
    return ParameterPtr(new Parameter(*this));
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

size_t Parameter::get_index() const
{
    return index;
}

bool Parameter::operator<(const Parameter& rhs) const
{
    return index<rhs.index;
}
