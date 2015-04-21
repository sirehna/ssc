/*
 * Constant.cpp
 *
 * \date 5 f�vr. 2013, 11:22:54
 *  \author cec
 */

#include "ssc/functors_for_optimizer/Constant.hpp"
#include "ssc/functors_for_optimizer/Null.hpp"
#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"
#include "ssc/functors_for_optimizer/N_ary.hpp"

#if defined(_MSC_VER)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#define not !
#endif

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
    const auto factor_ = factor;
    const auto val_ = val;
    set_value([factor_,val_]()->double {return factor_*val_;});
}

bool Constant::is_constant() const
{
    return true;
}

