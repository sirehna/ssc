/*
 * IfPositive.hpp
 *
 * \date 29 janv. 2013, 09:41:01
 * \author cec
 */

#ifndef IF_POSITIVE_HPP_
#define IF_POSITIVE_HPP_

#include "ssc/functors_for_optimizer/Node.hpp"

namespace ssc
{
    namespace functors_for_optimizer
    {
        class IfPositive : public Node
        {
            public:
                IfPositive(const NodePtr& test, const NodePtr& if_positive, const NodePtr& if_negative);
                NodePtr diff(const StatePtr& state) const;
                void accept(NodeVisitor& v) const;
                NodePtr clone() const;
                bool is_null() const;
                bool equals(const Node& rhs) const;
                std::string get_type() const;
                void update_lambda();
                NodePtr get_test() const;
                NodePtr get_positive() const;
                NodePtr get_negative() const;
                using Node::equals_derived;
                bool equals_derived(const IfPositive& rhs) const;

            private:
                IfPositive();//Disabled
                NodePtr test;
                NodePtr if_positive;
                NodePtr if_negative;

        };

        typedef TR1(shared_ptr)<IfPositive> IfPositivePtr;
    }
}
#endif /* IF_POSITIVE_HPP_ */
