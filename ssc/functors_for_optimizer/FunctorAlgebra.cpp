/*
 * FunctorAlgebra.cpp
 *
 * \date 1 f�vr. 2013, 15:29:58
 *  \author cec
 */

#include "ssc/functors_for_optimizer/FunctorAlgebra.hpp"
#include "ssc/functors_for_optimizer/Parameter.hpp"
#include "ssc/functors_for_optimizer/Difference.hpp"
#include "ssc/functors_for_optimizer/Sum.hpp"
#include "ssc/functors_for_optimizer/Divide.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/functors_for_optimizer/Pow.hpp"
#include "ssc/functors_for_optimizer/Null.hpp"
#include "ssc/functors_for_optimizer/Constant.hpp"
#include "ssc/functors_for_optimizer/Sin.hpp"
#include "ssc/functors_for_optimizer/Cos.hpp"
#include "ssc/functors_for_optimizer/Ln.hpp"
#include "ssc/functors_for_optimizer/Sign.hpp"
#include "ssc/functors_for_optimizer/Abs.hpp"
#include "ssc/functors_for_optimizer/Sqrt.hpp"

#include <cmath>
using namespace ssc::functors_for_optimizer;

#if defined(_MSC_VER)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#define not !
#endif

namespace ssc
{
    namespace functors_for_optimizer
    {

        Mult operator*(const Node& n1, const Node& n2)
        {
            if (n1.is_null()) return Mult(new Multiply(NullPtr(new Null()),n2.clone()));
            if (n2.is_null()) return Mult(new Multiply(NullPtr(new Null()),n1.clone()));
            return Mult(new Multiply(n1.clone(),n2.clone()));
        }

        Mult operator*(const Node& n1, const NodePtr& n2)
        {
            if (n1.is_null()) return Mult(new Multiply(NullPtr(new Null()),n2->clone()));
            if (n2->is_null()) return Mult(new Multiply(NullPtr(new Null()),n1.clone()));
            return Mult(new Multiply(n1.clone(),n2));
        }

        Mult operator*(const NodePtr& n1, const NodePtr& n2)
        {
            if (n1->is_null()) return Mult(new Multiply(NullPtr(new Null()),n2->clone()));
            if (n2->is_null()) return Mult(new Multiply(NullPtr(new Null()),n1->clone()));
            return Mult(new Multiply(n1,n2));
        }

        Mult operator*(const NodePtr& n1, const Node& n2)
        {
            if (n2.is_null()) return Mult(new Multiply(NullPtr(new Null()),n1->clone()));
            if (n1->is_null()) return Mult(new Multiply(NullPtr(new Null()),n2.clone()));
            return Mult(new Multiply(n1,n2.clone()));
        }

        NodePtr operator*(const NodePtr& n, const double d)
        {
            if (d == 0) return NullPtr(new Null());
            if (n->is_null()) return NullPtr(new Null());
            auto c = n->clone();
            c->multiply_by(d);
            c->update_lambda();
            return c;
        }

        NodePtr operator*(const double d, const NodePtr& n)
        {
            return n*d;
        }

        NodePtr operator*(const NodePtr& n1, const Null& n2)
        {
            (void) n1;
            (void) n2;
            return NullPtr(new Null());
        }

        NodePtr operator*(const Null& n1, const NodePtr& n2)
        {
            (void) n1;
            (void) n2;
            return NullPtr(new Null());
        }

        NodePtr operator*(const Node& n1, const Null& n2)
        {
            (void) n1;
            (void) n2;
            return NullPtr(new Null());
        }

        NodePtr operator*(const Null& n1, const Node& n2)
        {
            return n2*n1;
        }

        NodePtr operator*(const Node& n1, const Constant& n2)
        {
            auto ret = n1.clone();
            ret->multiply_by(n2.get_lambda()());
            return ret;
        }

        NodePtr operator*(const Constant& n1, const Node& n2)
        {
            return n2*n1;
        }

        NodePtr operator*(const NodePtr& n1, const Constant& n2)
        {
            auto ret = n1;
            ret->multiply_by(n2.get_lambda()());
            return ret;
        }

        NodePtr operator+(const Node& n1, const Node& n2)
        {
            return n1.clone() + n2.clone();
        }

        NodePtr operator+(const Node& n1, const NodePtr& n2)
        {
            return n1.clone() + n2;
        }

        NodePtr operator+(const NodePtr& n1, const NodePtr& n2)
        {
            if (n1->is_null()) return n2;
            if (n2->is_null()) return n1;
            return SumPtr(new Sum(n1,n2));
        }

        NodePtr operator+(const NodePtr& n1, const Node& n2)
        {
            return n1 + n2.clone();
        }

        NodePtr operator+(const NodePtr& n1, const double d)
        {
            if (d==0) return n1;
            ConstantPtr n2(new Constant(d));
            if (n1->is_null()) return n2;
            return n1 + n2;
        }

        NodePtr operator-(const double d, const NodePtr& n2)
        {
            ConstantPtr n1(new Constant(d));
            return n1-n2;
        }

        NodePtr operator-(const NodePtr& n1, const double d)
        {
            if (d==0) return n1;
            ConstantPtr n2(new Constant(d));
            return n1-n2;
        }

        NodePtr operator-(const NodePtr& n1, const NodePtr&n2)
        {
            if (n2->is_null()) return n1;
            auto n2_ = n2->clone();
            n2_->multiply_by(-1);
            n2_->update_lambda();
            if (n1->is_null()) return n2;
            return SumPtr(new Sum(n1,n2_));
        }

        NodePtr operator-(const NodePtr& n, const Parameter&p)
        {
            return n-p.clone();
        }

        NodePtr operator/(const Node& n1, const Node& n2)
        {
            return n1.clone()/n2.clone();
        }

        NodePtr operator/(const Node& n1, const NodePtr& n2)
        {
            return n1.clone()/n2;
        }

        NodePtr operator/(const NodePtr& n1, const NodePtr& n2)
        {
            if (n1->is_null()) return n1;
            if (n2->is_null())
            {
                THROW(__PRETTY_FUNCTION__, FunctorAlgebraException, "Division by zero");
            }
            return DividePtr(new Divide(n1,n2));
        }

        NodePtr operator/(const NodePtr& n1, const Node& n2)
        {
            return n1/n2.clone();
        }

        NodePtr operator/(const NodePtr& n, const double d)
        {
            if (d == 0)
            {
                THROW(__PRETTY_FUNCTION__, FunctorAlgebraException, "Division by zero");
            }
            auto c = n->clone();
            c->multiply_by(1./d);
            return c;
        }

        NodePtr operator/(const double d, const NodePtr& n)
        {
            if (d==0) return NullPtr(new Null());
            return ConstantPtr(new Constant(d))/n;
        }

        PowPtr pow(const NodePtr& n1, const double d)
        {
            return pow(n1, ConstantPtr(new Constant(d)));
        }

        PowPtr pow(const Node& n1, const Node& n2)
        {
            return pow(n1.clone(),n2.clone());
        }

        PowPtr pow(const NodePtr& n1, const Node& n2)
        {
            return pow(n1, n2.clone());
        }

        PowPtr pow(const Node& n1, const NodePtr& n2)
        {
            return pow(n1.clone(), n2);
        }

        PowPtr pow(const NodePtr& n1, const NodePtr& n2)
        {
            return PowPtr(new Pow(n1,n2));
        }

        NodePtr sin(const NodePtr& n)
        {
            if (n->is_null()) return n;
            return SinPtr(new Sin(n));
        }

        NodePtr cos(const NodePtr& n)
        {
            if (n->is_null()) return ConstantPtr(new Constant(1));
            return CosPtr(new Cos(n));
        }

        NodePtr cos(const Node& n)
        {
            if (n.is_null()) return ConstantPtr(new Constant(1));
            return CosPtr(new Cos(n.clone()));
        }

        NodePtr sign(const NodePtr& n)
        {
            if (n->is_null()) return ConstantPtr(new Constant(1));
            return SignPtr(new Sign(n));
        }

        NodePtr abs(const NodePtr& n)
        {
            if (n->is_null()) return NullPtr(new Null());
            return AbsPtr(new Abs(n));
        }

        NodePtr sqrt(const NodePtr& n)
        {
            if (n->is_null()) return NullPtr(new Null());
            if (n->is_constant()) return ConstantPtr(new Constant(std::sqrt(n->get_lambda()())));
            return SqrtPtr(new Sqrt(n));
        }

        bool operator==(const double v, const NodePtr& n)
        {
            return n==v;
        }
        bool operator!=(const NodePtr& n, const double v)
        {
            return not(n==v);
        }

        bool operator!=(const double v, const NodePtr& n)
        {
            return not(n==v);
        }

        bool operator==(const NodePtr& n1, const NodePtr& n2)
        {
            return *n1 == *n2;
        }

        bool operator!=(const NodePtr& n1, const NodePtr& n2)
        {
            return not(n1!=n2);
        }

        bool operator==(const Node& n1, const Node& n2)
        {
            return n1.equals(n2);
        }

        bool operator!=(const Node& n1, const Node& n2)
        {
            return not(n1==n2);
        }

        bool operator==(const NodePtr& n1, const double n2)
        {
            return *n1==Constant(n2);
        }

        bool operator!=(const Node& n1, const double n2)
        {
            return not(n1==Constant(n2));
        }
    }
}
