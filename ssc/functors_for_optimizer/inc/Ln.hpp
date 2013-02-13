/*
 * Ln.hpp
 *
 * \date 1 févr. 2013, 12:32:08
 *  \author cec
 */

#ifndef LN_HPP_
#define LN_HPP_

#include "Unary.hpp"

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/LnTest.cpp LnTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/LnTest.cpp LnTest expected output
 */

class Ln : public Unary
{
    public:
        Ln(const NodePtr& n_);
        std::string get_operator_name() const;
        NodePtr diff(const StatePtr& state) const;
        NodePtr clone() const;
        bool is_null() const;
        std::string get_type() const;
        NodePtr simplify() const;
};
typedef std::tr1::shared_ptr<Ln> LnPtr;

#endif /* LN_HPP_ */
