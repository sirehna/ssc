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
        class Constant;
        class Pow;
        class Difference;
        class Divide;
        class Sin;
        class Cos;
        class Ln;
        class PiecewiseConstantFunctor;
        class PiecewiseLinearFunctor;
        class PiecewiseParabolicFunctor;
        class SplineFunctor;
        class Sign;
        class Abs;
        class Sqrt;

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
                virtual void visit(const Sin& node) = 0;
                virtual void visit(const Cos& node) = 0;
                virtual void visit(const Ln& node) = 0;
                virtual void visit(const PiecewiseConstantFunctor& node) = 0;
                virtual void visit(const PiecewiseLinearFunctor& node) = 0;
                virtual void visit(const SplineFunctor& node) = 0;
                virtual void visit(const PiecewiseParabolicFunctor& node) = 0;
                virtual void visit(const Sign& node) = 0;
                virtual void visit(const Abs& node) = 0;
                virtual void visit(const Sqrt& node) = 0;

                virtual ~NodeVisitor() {};
        };
    }
}

#endif /* NODEVISITOR_HPP_ */
