/*
 * IfPositive.cpp
 *
 * \date 29 janv. 2013, 09:41:02
 * \author cec
 */

#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/functors_for_optimizer/IfPositive.hpp"
#include "ssc/functors_for_optimizer/Null.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"

using namespace ssc::functors_for_optimizer;

#if defined(_MSC_VER)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#define not !
#endif

IfPositive::IfPositive(const NodePtr& test_, const NodePtr& if_positive_, const NodePtr& if_negative_) :
        test(test_),if_positive(if_positive_),if_negative(if_negative_)
{
    update_lambda();
}

void IfPositive::update_lambda()
{
    const auto factor_ = factor;
    const auto test_ = test;
    const auto if_positive_ = if_positive;
    const auto if_negative_ = if_negative;
    value = ([factor_,test_,if_positive_,if_negative_]()->double
              {
                 return (test_->get_lambda()()>0) ? factor_*if_positive_->get_lambda()() : factor_*if_negative_->get_lambda()();
              });
}

NodePtr IfPositive::get_negative() const
{
    return if_negative;
}

NodePtr IfPositive::get_positive() const
{
    return if_positive;
}

NodePtr IfPositive::get_test() const
{
    return test;
}

NodePtr IfPositive::diff(const StatePtr& state) const
{
    (void)state;
    auto dpos = if_positive->diff(state);
    auto dneg = if_negative->diff(state);
    if (dpos->equals(*dneg)) return dpos;
    return IfPositivePtr(new IfPositive(test, dpos, dneg));
}

void IfPositive::accept(NodeVisitor& v) const
{
    v.visit(*this);
}

NodePtr IfPositive::clone() const
{
    return NodePtr(new IfPositive(*this));
}

bool IfPositive::is_null() const
{
    return (if_positive->is_null()) && (if_negative->is_null());
}

bool IfPositive::equals(const Node& rhs) const
{
    return rhs.equals_derived(*this);
}

bool IfPositive::equals_derived(const IfPositive& rhs) const
{
    return (if_positive->equals(*rhs.if_positive)) && (if_negative->equals(*rhs.if_negative));
}

std::string IfPositive::get_type() const
{
    return "if";
}
