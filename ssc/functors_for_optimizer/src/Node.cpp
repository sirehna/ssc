/*
 * Node.cpp
 *
 * \date 22 janv. 2013, 08:23:20
 *  \author cec
 */

#include "Node.hpp"

ValType::ValType() : lambda(1), _f([]()->double{return 0;})
{

}

ValType::ValType(const double& l, const std::function<double ()>& f) : lambda(l), _f(f)
{
}

ValType::ValType(const std::function<double ()>& f) : lambda(1), _f(f)
{

}

double ValType::operator()() const
{
    return lambda*_f();
}

ValType ValType::operator*(const double& l) const
{
    return ValType(lambda*l, _f);
}

ValType operator*(const double& l, const ValType& v)
{
    return v*l;
}
