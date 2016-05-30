/*
 * NodeVisitor.hpp
 *
 * \date 1 f�vr. 2013, 10:10:20
 *  \author cec
 */

#ifndef NODEVISITOR_HPP_
#define NODEVISITOR_HPP_

namespace ssc
{
    namespace functors_for_optimizer
    {
        class Sum;
        class Multiply;
        class State;
        class Parameter;
        class Null;
        class Unary;
        class Constant;
        class Pow;
        class Difference;
        class Divide;

        class NodeVisitor
        {
            public:
                virtual void visit(const Pow& node) = 0;
                virtual void visit(const Difference& node) = 0;
                virtual void visit(const Divide& node) = 0;
                virtual void visit(const Sum& node) = 0;
                virtual void visit(const Multiply& node) = 0;
                virtual void visit(const State& node) = 0;
                virtual void visit(const Parameter& node) = 0;
                virtual void visit(const Constant& node) = 0;
                virtual void visit(const Null& node) = 0;
                virtual void visit(const Unary& node) = 0;
                virtual ~NodeVisitor() {};
        };
    }
}

#endif /* NODEVISITOR_HPP_ */
