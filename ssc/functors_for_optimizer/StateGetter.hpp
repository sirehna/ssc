/*
 * StateGetter.hpp
 *
 * \date 20 f�vr. 2013, 12:53:19
 *  \author cec
 */

#ifndef STATEGETTER_HPP_
#define STATEGETTER_HPP_

#include "ssc/functors_for_optimizer/NodeVisitor.hpp"
#include "ssc/functors_for_optimizer/Node.hpp"


/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/StateGetterTest.cpp StateGetterTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/StateGetterTest.cpp StateGetterTest expected output
 */
namespace ssc
{
    namespace functors_for_optimizer
    {
        class State;
        typedef TR1(shared_ptr)<State> StatePtr;
        typedef std::vector<StatePtr> StateList;


        class StateGetter : public NodeVisitor
        {
            public:
                StateGetter();
                StateGetter(const StateList& list);
                void operator()(const NodePtr& f);
                void operator()(const std::vector<NodePtr>& g);
                std::vector<StatePtr> get() const;
                void visit(const Pow& node);
                void visit(const Divide& node);
                void visit(const Difference& node);
                void visit(const Multiply& node);
                void visit(const Sum& node);
                void visit(const State& node);
                void visit(const Parameter& node);
                void visit(const Null& node);
                void visit(const Unary& node);
                void visit(const Constant& node);

            private:
                class StateGetter_pimpl;
                TR1(shared_ptr)<StateGetter_pimpl> pimpl;
        };
    }
}

#endif /* STATEGETTER_HPP_ */
