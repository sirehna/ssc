/*
 * SerializeReversePolish.cpp
 *
 * \date 28 f�vr. 2013, 16:48:42
 *  \author cec
 */

#include "ssc/functors_for_optimizer/SerializeReversePolish.hpp"
#include "ssc/functors_for_optimizer/Pow.hpp"
#include "ssc/functors_for_optimizer/Divide.hpp"
#include "ssc/functors_for_optimizer/Difference.hpp"
#include "ssc/functors_for_optimizer/N_ary.hpp"
#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/functors_for_optimizer/Null.hpp"
#include "ssc/functors_for_optimizer/Unary.hpp"
#include "ssc/functors_for_optimizer/Constant.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/functors_for_optimizer/Sum.hpp"


#include <cmath>

using namespace ssc::functors_for_optimizer;

SerializeReversePolish::SerializeReversePolish(std::ostream& os_) : os(os_)
{

}

void SerializeReversePolish::visit_nary(const N_ary& node)
{
    auto sons = node.get_sons();
    if (sons.empty())
    {
        os << "0";
    }
    else
    {
        serialize_multiplicative_factor(node.get_multiplicative_factor());
        {
            os << node.get_type() << "(";
            for (size_t i = 0 ; i < sons.size()-1 ; ++i)
            {
                sons.at(i)->accept(*this);
                os << ",";
            }
            sons.back()->accept(*this);
            os << ")";
        }
    }
}

void SerializeReversePolish::visit(const Sum& node)
{
    visit_nary(node);
}

void SerializeReversePolish::visit(const Multiply& node)
{
    visit_nary(node);
}

void SerializeReversePolish::visit(const Difference& node)
{
    serialize_multiplicative_factor(node.get_multiplicative_factor());
    os << node.get_type();
    os << "(";
    node.get_lhs()->accept(*this);
    os << ",";
    node.get_rhs()->accept(*this);
    os << ")";
}

void SerializeReversePolish::visit(const Divide& node)
{
    serialize_multiplicative_factor(node.get_multiplicative_factor());
    os << node.get_type();
    os << "(";
    node.get_lhs()->accept(*this);
    os << ",";
    node.get_rhs()->accept(*this);
    os << ")";
}

void SerializeReversePolish::visit(const Pow& node)
{
    serialize_multiplicative_factor(node.get_multiplicative_factor());
    os << node.get_type();
    os << "(";
    node.get_lhs()->accept(*this);
    os << ",";
    node.get_rhs()->accept(*this);
    os << ")";
}

void SerializeReversePolish::visit(const State& node)
{
    serialize_multiplicative_factor(node.get_multiplicative_factor());
    os << node.get_name();
}

void SerializeReversePolish::visit(const Parameter& node)
{
    os << "p" << node.get_index();
}

void SerializeReversePolish::visit(const Null& node)
{
    (void)node;
    os << "0";
}

void SerializeReversePolish::visit(const Unary& node)
{
    serialize_multiplicative_factor(node.get_multiplicative_factor());
    os << node.get_type() << "(";
    node.get_son()->accept(*this);
    os << ")";
}

void SerializeReversePolish::visit(const Constant& node)
{
    os << node.get_lambda()();
}

void SerializeReversePolish::serialize_multiplicative_factor(const double& k)
{
    if (k == -1)
    {
        os << "-";
    }
    else if (k == 1)
    {
    }
    else
    {
        if (k < 0)
        {
            os << "-" << fabs(k);
        }
        else
        {
            os << k;
        }
        os << "*";
    }
}
