/*
 * NodeVisitor.hpp
 *
 * \date 1 févr. 2013, 10:10:20
 *  \author cec
 */

#ifndef NODEVISITOR_HPP_
#define NODEVISITOR_HPP_

class Binary;
class N_ary;
class State;
class Parameter;
class Null;
class Unary;
class Constant;
class Pow;

class NodeVisitor
{
    public:
        virtual void visit(const Binary& node) = 0;
        virtual void visit(const N_ary& node) = 0;
        virtual void visit(const State& node) = 0;
        virtual void visit(const Parameter& node) = 0;
        virtual void visit(const Constant& node) = 0;
        virtual void visit(const Null& node) = 0;
        virtual void visit(const Unary& node) = 0;
        virtual ~NodeVisitor() {};
};

#endif /* NODEVISITOR_HPP_ */
