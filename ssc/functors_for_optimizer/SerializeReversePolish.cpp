/*
 * SerializeReversePolish.cpp
 *
 * \date 28 févr. 2013, 16:48:42
 * \author cec
 */

#include "ssc/functors_for_optimizer/SerializeReversePolish.hpp"
#include "ssc/functors_for_optimizer/Pow.hpp"
#include "ssc/functors_for_optimizer/Divide.hpp"
#include "ssc/functors_for_optimizer/Difference.hpp"
#include "ssc/functors_for_optimizer/N_ary.hpp"
#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/functors_for_optimizer/Null.hpp"
#include "ssc/functors_for_optimizer/Sin.hpp"
#include "ssc/functors_for_optimizer/Sign.hpp"
#include "ssc/functors_for_optimizer/Abs.hpp"
#include "ssc/functors_for_optimizer/Cos.hpp"
#include "ssc/functors_for_optimizer/Ln.hpp"
#include "ssc/functors_for_optimizer/Constant.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/functors_for_optimizer/Sum.hpp"
#include "ssc/functors_for_optimizer/Sqrt.hpp"
#include "ssc/functors_for_optimizer/PiecewiseConstantFunctor.hpp"
#include "ssc/functors_for_optimizer/PiecewiseLinearFunctor.hpp"
#include "ssc/functors_for_optimizer/PiecewiseParabolicFunctor.hpp"
#include "ssc/functors_for_optimizer/SplineFunctor.hpp"
#include "ssc/functors_for_optimizer/Node.hpp"
#include "ssc/functors_for_optimizer/IfPositive.hpp"


#include <cmath>
#include <sstream>

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

void SerializeReversePolish::visit(const Sin& node)
{
    serialize_multiplicative_factor(node.get_multiplicative_factor());
    os << "sin(";
    node.get_son()->accept(*this);
    os << ")";
}

void SerializeReversePolish::visit(const Sign& node)
{
    serialize_multiplicative_factor(node.get_multiplicative_factor());
    os << "sign(";
    node.get_son()->accept(*this);
    os << ")";
}

void SerializeReversePolish::visit(const Abs& node)
{
    serialize_multiplicative_factor(node.get_multiplicative_factor());
    os << "abs(";
    node.get_son()->accept(*this);
    os << ")";
}

void SerializeReversePolish::visit(const Cos& node)
{
    serialize_multiplicative_factor(node.get_multiplicative_factor());
    os << "cos(";
    node.get_son()->accept(*this);
    os << ")";
}

void SerializeReversePolish::visit(const Sqrt& node)
{
    serialize_multiplicative_factor(node.get_multiplicative_factor());
    os << "sqrt(";
    node.get_son()->accept(*this);
    os << ")";
}

void SerializeReversePolish::visit(const Ln& node)
{
    serialize_multiplicative_factor(node.get_multiplicative_factor());
    os << "ln(";
    node.get_son()->accept(*this);
    os << ")";
}

void SerializeReversePolish::visit(const PiecewiseConstantFunctor& node)
{
    serialize_multiplicative_factor(node.get_multiplicative_factor());
    os << "piecewise_constant(";
    node.get_son()->accept(*this);
    os << ")";
}

void SerializeReversePolish::visit(const PiecewiseLinearFunctor& node)
{
    serialize_multiplicative_factor(node.get_multiplicative_factor());
    os << "piecewise_linear(";
    node.get_son()->accept(*this);
    os << ")";
}

void SerializeReversePolish::visit(const PiecewiseParabolicFunctor& node)
{
    serialize_multiplicative_factor(node.get_multiplicative_factor());
    os << "piecewise_parabolic(";
    node.get_son()->accept(*this);
    os << ")";
}

void SerializeReversePolish::visit(const SplineFunctor& node)
{
    serialize_multiplicative_factor(node.get_multiplicative_factor());
    os << "spline(";
    node.get_son()->accept(*this);
    os << ")";
}
void SerializeReversePolish::visit(const Constant& node)
{
    os << node.get_lambda()();
}

void SerializeReversePolish::visit(const IfPositive& node)
{
    serialize_multiplicative_factor(node.get_multiplicative_factor());
    os << "if_positive(";
    node.get_test()->accept(*this);
    os << ",";
    node.get_positive()->accept(*this);
    os << ",";
    node.get_negative()->accept(*this);
    os << ")";
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

std::string ssc::functors_for_optimizer::serialize(const NodePtr& node)
{
    std::stringstream ss;
    SerializeReversePolish S(ss);
    node->accept(S);
    return ss.str();
}
