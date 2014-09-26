/*
 * Binary.hpp
 *
 * \date 31 janv. 2013, 16:06:42
 *  \author cec
 */

#ifndef BINARY_HPP_
#define BINARY_HPP_

#include "Node.hpp"
#include <string>

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/BinaryTest.cpp BinaryTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/BinaryTest.cpp BinaryTest expected output
 */

class Binary : public Node
{
    public:
        Binary(const NodePtr& n1, const NodePtr& n2);
        ~Binary() {}
        void accept(NodeVisitor& v) const;
        virtual std::string get_operator_name() const = 0;
        NodePtr get_lhs() const;
        NodePtr get_rhs() const;

    protected:
        NodePtr n1_;
        NodePtr n2_;
        void set_value(const std::function<double()>& val);
    private:
        Binary();
};

#endif /* BINARY_HPP_ */
