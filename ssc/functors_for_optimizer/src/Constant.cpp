/*
 * Constant.cpp
 *
 * \date 5 févr. 2013, 11:22:54
 *  \author cec
 */

#include "Constant.hpp"
#include "Null.hpp"
#include "State.hpp"
#include "NodeVisitor.hpp"
#include "N_ary.hpp"

Constant::Constant(const double& v) : val(v)
{
    update_lambda();
}

NodePtr Constant::diff(const StatePtr& state) const
{
    if (state->get_index()){}
    return NodePtr(new Null());
}

bool Constant::operator==(const Constant& rhs) const
{
    return val==rhs.val;
}

bool Constant::operator!=(const Constant& rhs) const
{
    return not(*this==rhs);
}

void Constant::accept(NodeVisitor& v) const
{
    v.visit(*this);
}

NodePtr Constant::clone() const
{
    return NodePtr(new Constant(*this));
}

bool Constant::is_null() const
{
    return val==0;
}

bool Constant::equals(const Node& rhs) const
{
    return rhs.equals_derived(*this);
}

bool Constant::equals_derived(const Constant& rhs) const
{
    return rhs.val==val;
}

bool Constant::equals_derived(const N_ary& rhs) const
{
    return rhs.equals_derived(*this);
}

std::string Constant::get_type() const
{
    return "Constant";
}

bool Constant::is_negative() const
{
    return factor*val<0;
}

void Constant::update_lambda()
{
    set_value([factor,val]()->double {return factor*val;});
}
