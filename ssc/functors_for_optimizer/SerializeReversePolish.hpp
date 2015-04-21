/*
 * SerializeReversePolish.hpp
 *
 * \date 28 f�vr. 2013, 16:48:41
 *  \author cec
 */

#ifndef SERIALIZEREVERSEPOLISH_HPP_
#define SERIALIZEREVERSEPOLISH_HPP_

#include "NodeVisitor.hpp"
#include <sstream>


/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/SerializeReversePolishTest.cpp SerializeReversePolishTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/SerializeReversePolishTest.cpp SerializeReversePolishTest expected output
 */
class N_ary;
class SerializeReversePolish : public NodeVisitor
{
    public:
        SerializeReversePolish(std::ostream& os_);
        ~SerializeReversePolish() {}
        void visit(const Binary& node);
        void visit(const Sum& node);
        void visit(const Multiply& node);
        void visit_nary(const N_ary& node);
        void visit(const State& node);
        void visit(const Parameter& node);
        void visit(const Null& node);
        void visit(const Unary& node);
        void visit(const Constant& node);
    private:
        SerializeReversePolish();
        void serialize_multiplicative_factor(const double& k);
        std::ostream& os;
};

#endif /* SERIALIZEREVERSEPOLISH_HPP_ */
