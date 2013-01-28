/*
 * NodeSerializationVisitor.hpp
 *
 * \date 28 janv. 2013, 12:42:30
 *  \author cec
 */

#ifndef NODESERIALIZATIONVISITOR_HPP_
#define NODESERIALIZATIONVISITOR_HPP_

#include "NodeAbstractVisitor.hpp"
#include <string>
#include <sstream>

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/NodeSerializationVisitorTest.cpp NodeSerializationVisitorTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/NodeSerializationVisitorTest.cpp NodeSerializationVisitorTest expected output
 */

class NodeSerializationVisitor : public NodeAbstractVisitor
{
    public:
        NodeSerializationVisitor(std::ostream& os_);
        ~NodeSerializationVisitor();
        void visit(const Multiply& node);
        void visit(const Pow& node);
        void visit(const State& node);
        void visit(const Parameter& node);

    private:
        NodeSerializationVisitor();
        NodeSerializationVisitor(const NodeSerializationVisitor& rhs);
        void parenthezise(const Multiply& node);
        void parenthezise(const Pow& node);
        void parenthezise(const State& node);
        void parenthezise(const Parameter& node);
        std::ostream& os;
};

class Node;
::std::ostream& operator<<(::std::ostream& os, const Node& node);

#endif /* NODESERIALIZATIONVISITOR_HPP_ */
