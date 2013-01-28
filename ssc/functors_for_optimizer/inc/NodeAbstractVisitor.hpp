/*
 * NodeAbstractVisitor.hpp
 *
 * \date 28 janv. 2013, 12:55:53
 *  \author cec
 */

#ifndef NODEABSTRACTVISITOR_HPP_
#define NODEABSTRACTVISITOR_HPP_

class Multiply;
class Pow;
class State;
class Parameter;

class NodeAbstractVisitor
{
    public:
        virtual void visit(const Multiply& node) = 0;
        virtual void visit(const Pow& node) = 0;
        virtual void visit(const State& node) = 0;
        virtual void visit(const Parameter& node) = 0;
        virtual ~NodeAbstractVisitor() {};
};


#endif /* NODEABSTRACTVISITOR_HPP_ */
