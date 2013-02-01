/*
 * FunctorAlgebra.cpp
 *
 * \date 1 févr. 2013, 15:29:58
 *  \author cec
 */

#include "FunctorAlgebra.hpp"

Mult operator*(const Node& n1, const Node& n2)
{
    return Mult(new Multiply(n1.clone(),n2.clone()));
}

Mult operator*(const Node& n1, const NodePtr& n2)
{
    return Mult(new Multiply(n1.clone(),n2));
}

Mult operator*(const NodePtr& n1, const NodePtr& n2)
{
    return Mult(new Multiply(n1,n2));
}

Mult operator*(const NodePtr& n1, const Node& n2)
{
    return Mult(new Multiply(n1,n2.clone()));
}

NodePtr operator*(const NodePtr& n, const double& d)
{
    if (d == 0) return NullPtr(new Null());
    auto c = n->clone();
    c->multiply_by(d);
    return c;
}

NodePtr operator*(const double& d, const NodePtr& n)
{
    return n*d;
}

NullPtr operator*(const NodePtr& n1, const Null& n2)
{
    n1->multiply_by(1);
    if (n2.get_value()) {}
    return NullPtr(new Null());
}

NullPtr operator*(const Null& n1, const NodePtr& n2)
{
    n2->multiply_by(1);
    if (n1.get_value()) {}
    return NullPtr(new Null());
}

NullPtr operator*(const Node& n1, const Null& n2)
{
    n1.get_value();
    if (n2.get_value()) {}
    return NullPtr(new Null());
}

NullPtr operator*(const Null& n1, const Node& n2)
{
    return n2*n1;
}



SumPtr operator+(const Node& n1, const Node& n2)
{
    return SumPtr(new Sum(n1.clone(),n2.clone()));
}

SumPtr operator+(const Node& n1, const NodePtr& n2)
{
    return SumPtr(new Sum(n1.clone(),n2));
}

SumPtr operator+(const NodePtr& n1, const NodePtr& n2)
{
    return SumPtr(new Sum(n1,n2));
}

SumPtr operator+(const NodePtr& n1, const Node& n2)
{
    return SumPtr(new Sum(n1,n2.clone()));
}

NodePtr operator+(const NodePtr& n1, const Null& n2)
{
    if (n2.get_value()) {}
    return n1;
}

NodePtr operator+(const Null& n1, const NodePtr& n2)
{
    n1.get_value();
    return n2;
}

NodePtr operator+(const Node& n1, const Null& n2)
{
    if (n2.get_value()) {}
    return n1.clone();
}

NodePtr operator+(const Null& n1, const Node& n2)
{
    if (n1.get_value()) {}
    return n2.clone();
}


DividePtr operator/(const Node& n1, const Node& n2)
{
    return DividePtr(new Divide(n1.clone(),n2.clone()));
}

DividePtr operator/(const Node& n1, const NodePtr& n2)
{
    return DividePtr(new Divide(n1.clone(),n2));
}

DividePtr operator/(const NodePtr& n1, const NodePtr& n2)
{
    return DividePtr(new Divide(n1,n2));
}

DividePtr operator/(const NodePtr& n1, const Node& n2)
{
    return DividePtr(new Divide(n1,n2.clone()));
}

NodePtr operator/(const NodePtr& n, const double& d)
{
    if (d == 0)
    {
        THROW("operator /(const NodePtr&, const double&)", FunctorAlgebraException, "Division by zero");


    }
    auto c = n->clone();
    c->multiply_by(1./d);
    return c;
}

NodePtr operator/(const double& d, const NodePtr& n)
{
    return n/d;
}

NullPtr operator/(const NodePtr& n1, const Null& n2)
{
    THROW("operator /(const NodePtr&, const Null&)", FunctorAlgebraException, "Division by zero");


    n1->multiply_by(1);
    if (n2.get_value()) {}
    return NullPtr(new Null());
}

NullPtr operator/(const Null& n1, const NodePtr& n2)
{
    n2->multiply_by(1);
    if (n1.get_value()) {}
    return NullPtr(new Null());
}

NullPtr operator/(const Node& n1, const Null& n2)
{
    THROW("operator /(const Node&, const Null&)", FunctorAlgebraException, "Division by zero");


    n1.get_value();
    if (n2.get_value()) {}
    return NullPtr(new Null());
}

NullPtr operator/(const Null& n1, const Node& n2)
{
    if (n1.get_value()) {}
    if (n2.get_value()) {}
    return NullPtr(new Null());
}

PowPtr pow(const Node& n1, const double& d)
{
    return PowPtr(new Pow(n1.clone(),ConstantPtr(new Constant(d))));
}

PowPtr pow(const NodePtr& n1, const double& d)
{
    return PowPtr(new Pow(n1,ConstantPtr(new Constant(d))));
}

PowPtr pow(const Node& n1, const Node& n2)
{
    return PowPtr(new Pow(n1.clone(),n2.clone()));
}

PowPtr pow(const NodePtr& n1, const Node& n2)
{
    return PowPtr(new Pow(n1,n2.clone()));
}

PowPtr pow(const Node& n1, const NodePtr& n2)
{
    return PowPtr(new Pow(n1.clone(),n2));
}

PowPtr pow(const NodePtr& n1, const NodePtr& n2)
{
    return PowPtr(new Pow(n1,n2));
}

NullPtr pow(const Null& n1, const Node& n2)
{
    if (n1.get_value()()+n2.get_value()()) {}
    return NullPtr(new Null());
}

NullPtr pow(const Null& n1, const NodePtr& n2)
{
    if (n1.get_value()()+n2->get_value()()) {}
    return NullPtr(new Null());
}

NullPtr pow(const NullPtr& n1, const Node& n2)
{
    if (n2.get_value()()) {}
    return n1;
}

NullPtr pow(const NullPtr& n1, const NodePtr& n2)
{
    if (n2->get_value()()) {}
    return n1;
}
