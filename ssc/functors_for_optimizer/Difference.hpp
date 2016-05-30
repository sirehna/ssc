/*
 * Difference.hpp
 *
 * \date 1 f�vr. 2013, 09:22:47
 *  \author cec
 */

#ifndef DIFFERENCE_HPP_
#define DIFFERENCE_HPP_

#include "ssc/functors_for_optimizer/Binary.hpp"
/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/DifferenceTest.cpp DifferenceTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/DifferenceTest.cpp DifferenceTest expected output
 */


namespace ssc
{
    namespace functors_for_optimizer
    {
        class Difference : public Binary
        {
            public:
                Difference(const NodePtr& n1, const NodePtr& n2);
                std::string get_operator_name() const;
                NodePtr clone() const;
                NodePtr diff(const StatePtr& state) const;
                bool is_null() const;
                bool equals(const Node& rhs) const;
                using Node::equals_derived;
                bool equals_derived(const Difference& rhs) const;
                std::string get_type() const;
                NodePtr simplify() const;
                bool is_constant() const;
                void update_lambda();
                void accept(NodeVisitor& v) const;
        };

        typedef TR1(shared_ptr)<Difference> DiffPtr;
    }
}

#endif /* DIFFERENCE_HPP_ */
