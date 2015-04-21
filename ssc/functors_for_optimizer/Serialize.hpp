/*
 * Serialize.hpp
 *
 * \date 1 f�vr. 2013, 10:09:29
 *  \author cec
 */

#ifndef SERIALIZE_HPP_
#define SERIALIZE_HPP_
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"
#include <sstream>
#include "ssc/macros/tr1_macros.hpp"
#include TR1INC(memory)


/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/SerializeTest.cpp SerializeTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/SerializeTest.cpp SerializeTest expected output
 */
namespace ssc
{
    namespace functors_for_optimizer
    {
        class Serialize : public NodeVisitor
        {
            public:
                Serialize(std::ostream& os_);
                ~Serialize() {}
                void visit(const Binary& node);
                void visit(const Multiply& node);
                void visit(const Sum& node);
                void visit(const State& node);
                void visit(const Parameter& node);
                void visit(const Null& node);
                void visit(const Unary& node);
                void visit(const Constant& node);
            private:
                Serialize();
                void serialize_multiplicative_factor(const double& k);
                std::ostream& os;
                bool parenthesize_next_node;
        };

        class Node;
        ::std::ostream& operator<<(::std::ostream& os, const ssc::functors_for_optimizer::Node& node);
        ::std::ostream& operator<<(::std::ostream& os, const TR1(shared_ptr)<ssc::functors_for_optimizer::Node>& node);

    }
}

#endif /* SERIALIZE_HPP_ */
