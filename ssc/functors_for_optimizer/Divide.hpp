/*
 * Divide.hpp
 *
 * \date 1 f�vr. 2013, 08:59:33
 *  \author cec
 */

#ifndef DIVIDE_HPP_
#define DIVIDE_HPP_

#include "ssc/functors_for_optimizer/Binary.hpp"

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/DivideTest.cpp DivideTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/DivideTest.cpp DivideTest expected output
 */

namespace ssc
{
    namespace functors_for_optimizer
    {
        class Divide : public Binary
        {
            public:
                Divide(const NodePtr& n1, const NodePtr& n2);
                NodePtr diff(const StatePtr& state) const;
                std::string get_operator_name() const;
                NodePtr clone() const;
                bool is_null() const;
                bool equals(const Node& rhs) const;
                using Node::equals_derived;
                bool equals_derived(const Divide& rhs) const;
                std::string get_type() const;
                NodePtr simplify() const;
                bool must_parenthesize() const;
                bool is_constant() const;
                void update_lambda();
        };

        typedef TR1(shared_ptr)<Divide> DividePtr;
    }
}
#endif /* DIVIDE_HPP_ */
