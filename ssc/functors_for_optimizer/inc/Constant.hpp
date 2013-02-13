/*
 * Constant.hpp
 *
 * \date 5 févr. 2013, 11:22:54
 *  \author cec
 */

#ifndef CONSTANT_HPP_
#define CONSTANT_HPP_

#include "Nullary.hpp"

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/ConstantTest.cpp ConstantTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/ConstantTest.cpp ConstantTest expected output
 */

class Constant;
typedef std::tr1::shared_ptr<Constant> ConstantPtr;

class Constant : public Nullary
{
    public:
        Constant(const double& v);
        NodePtr diff(const StatePtr& state) const;
        bool operator==(const Constant& rhs) const;
        bool operator!=(const Constant& rhs) const;
        void accept(NodeVisitor& v) const;
        NodePtr clone() const;
        bool is_null() const;
        bool equals(const Node& rhs) const;
        using Node::equals_derived;
        bool equals_derived(const Constant& rhs) const;
        bool equals_derived(const N_ary& rhs) const;
        std::string get_type() const;

    private:
        Constant();
        double val;
};



#endif /* CONSTANT_HPP_ */
