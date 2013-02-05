/*
 * Binary.hpp
 *
 * \date 31 janv. 2013, 16:06:42
 *  \author cec
 */

#ifndef NARY_HPP_
#define NARY_HPP_

#include "Node.hpp"
#include <string>
#include <vector>

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/BinaryTest.cpp BinaryTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/BinaryTest.cpp BinaryTest expected output
 */

class N_ary : public Node
{
    public:
        N_ary(const NodePtr& n1, const NodePtr& n2);
        N_ary(const std::vector<NodePtr>& nodes);
        ~N_ary() {}
        std::vector<NodePtr> get_sons() const;
        void accept(NodeVisitor& v) const;
        virtual std::string get_operator_name() const = 0;
    protected:
        std::vector<NodePtr> sons;
        void set_value(const std::function<double()>& val);
    private:
        N_ary();
};

#endif /* ARY_HPP_ */
