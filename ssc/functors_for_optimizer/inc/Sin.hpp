/*
 * Sin.hpp
 *
 * \date 1 févr. 2013, 14:24:01
 *  \author cec
 */

#ifndef SIN_HPP_
#define SIN_HPP_

#include "Unary.hpp"

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/SinTest.cpp SinTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/SinTest.cpp SinTest expected output
 */



class Sin : public Unary
{
    public:
        Sin(const NodePtr& n_);
        std::string get_operator_name() const;
        NodePtr diff(const StatePtr& state) const;
        NodePtr clone() const;
        bool is_null() const;
        bool equals(const Node& rhs) const;
        //bool equals(const Sin& rhs) const;
        std::string get_type() const;
        NodePtr simplify() const;
};

typedef std::tr1::shared_ptr<Sin> SinPtr;
#endif /* SIN_HPP_ */
