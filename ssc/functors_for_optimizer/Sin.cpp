/*
 * Sin.cpp
 *
 * \date 1 f�vr. 2013, 14:24:01
 *  \author cec
 */

#include "ssc/functors_for_optimizer/Sin.hpp"
#include "ssc/functors_for_optimizer/Cos.hpp"
#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/functors_for_optimizer/Node.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/functors_for_optimizer/Constant.hpp"
#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"
#include <cmath>
#include <string>

using namespace ssc::functors_for_optimizer;

Sin::Sin(const NodePtr& n_) : Unary(n_)
{
    update_lambda();
}

void Sin::update_lambda()
{
    const auto n_ = n;
    const auto factor_ = factor;
    set_value([n_,factor_]()->double {return factor_*std::sin(n_->get_lambda()());});
}

std::string Sin::get_operator_name() const
{
    return "sin";
}

NodePtr Sin::diff(const StatePtr& state) const
{
    auto du_dstate = n->diff(state);
    auto dv_dstate = Cos(n->clone()).clone();
    if (n->diff(state)->equals_derived(Constant(1)))
    {
        return dv_dstate;
    }
    return du_dstate*dv_dstate;
}


NodePtr Sin::clone() const
{
    return NodePtr(new Sin(*this));
}

bool Sin::is_null() const
{
    return false;
}

bool Sin::equals(const Node& rhs) const
{
    (void) rhs;
        return false;
        //return rhs.equals_derived(*this);
}

std::string Sin::get_type() const
{
    return "Sin";
}

void Sin::accept(NodeVisitor& v) const
{
    v.visit(*this);
}
