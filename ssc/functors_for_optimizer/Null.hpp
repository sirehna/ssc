/*
 * Null.hpp
 *
 * \date 29 janv. 2013, 09:40:10
 *  \author cec
 */

#ifndef NULL_HPP_
#define NULL_HPP_

#include "ssc/functors_for_optimizer/Nullary.hpp"

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/NullTest.cpp NullTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/NullTest.cpp NullTest expected output
 */

namespace ssc
{
    namespace functors_for_optimizer
    {
        class Null : public Nullary
        {
            public:
                Null();
                NodePtr diff(const StatePtr& state) const;
                void accept(NodeVisitor& v) const;
                NodePtr clone() const;
                bool is_null() const;
                bool equals(const Node& rhs) const;
                using Node::equals_derived;
                bool equals_derived(const Null& rhs) const;
                std::string get_type() const;
                bool is_constant() const;
                void update_lambda();
        };
        typedef TR1(shared_ptr)<Null> NullPtr;
    }
}
#endif /* NULL_HPP_ */
