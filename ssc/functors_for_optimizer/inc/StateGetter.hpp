/*
 * StateGetter.hpp
 *
 * \date 20 févr. 2013, 12:53:19
 *  \author cec
 */

#ifndef STATEGETTER_HPP_
#define STATEGETTER_HPP_

#include "NodeVisitor.hpp"
#include "Node.hpp"


/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/StateGetterTest.cpp StateGetterTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/StateGetterTest.cpp StateGetterTest expected output
 */

class StateGetter : public NodeVisitor
{
    public:
        StateGetter();
        void operator()(const NodePtr& f);
        void operator()(const std::vector<NodePtr>& g);
        std::vector<StatePtr> get() const;
        void visit(const Binary& node);
        void visit(const Multiply& node);
        void visit(const Sum& node);
        void visit(const State& node);
        void visit(const Parameter& node);
        void visit(const Null& node);
        void visit(const Unary& node);
        void visit(const Constant& node);

    private:
        class StateGetter_pimpl;
        std::tr1::shared_ptr<StateGetter_pimpl> pimpl;
};

#endif /* STATEGETTER_HPP_ */
