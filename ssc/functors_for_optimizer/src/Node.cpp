/*
 * Node.cpp
 *
 * \date 29 janv. 2013, 15:32:23
 *  \author cec
 */


#include "Node.hpp"


Node::Node() : lambda(1), value([&lambda]()->double{return lambda;})
{

}

std::function<double()> Node::get_value() const
{
    return value;
}

void Node::multiply_by(const double& k)
{
    lambda *= k;
}

bool Node::is_null() const
{
    return false;
}
