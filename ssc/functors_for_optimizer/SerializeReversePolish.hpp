/*
 * SerializeReversePolish.hpp
 *
 * \date 28 f�vr. 2013, 16:48:41
 *  \author cec
 */

#ifndef SERIALIZEREVERSEPOLISH_HPP_
#define SERIALIZEREVERSEPOLISH_HPP_

#include "ssc/functors_for_optimizer/NodeVisitor.hpp"
#include <sstream>
#include "ssc/macros/tr1_macros.hpp"
#include TR1INC(memory)


/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/SerializeReversePolishTest.cpp SerializeReversePolishTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/SerializeReversePolishTest.cpp SerializeReversePolishTest expected output
 */
namespace ssc
{
    namespace functors_for_optimizer
    {
        class N_ary;
        class SerializeReversePolish : public NodeVisitor
        {
            public:
                SerializeReversePolish(std::ostream& os_);
                ~SerializeReversePolish() {}
                void visit(const Pow& node);
                void visit(const Divide& node);
                void visit(const Difference& node);
                void visit(const Sum& node);
                void visit(const Multiply& node);
                void visit_nary(const N_ary& node);
                void visit(const State& node);
                void visit(const Parameter& node);
                void visit(const Null& node);
                void visit(const Sin& node);
                void visit(const Cos& node);
                void visit(const Ln& node);
                void visit(const Constant& node);
                void visit(const PiecewiseConstantFunctor& node);
                void visit(const PiecewiseLinearFunctor& node);
                void visit(const SplineFunctor& node);
                void visit(const PiecewiseParabolicFunctor& node);
                void visit(const Sign& node);
                void visit(const Abs& node);
                void visit(const Sqrt& node);
            private:
                SerializeReversePolish();
                void serialize_multiplicative_factor(const double& k);
                std::ostream& os;
        };
        class Node;
        typedef TR1(shared_ptr)<Node> NodePtr;
        std::string serialize(const NodePtr& node);
    }
}

#endif /* SERIALIZEREVERSEPOLISH_HPP_ */
