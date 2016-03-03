/*
 * Abs.hpp
 *
 * \date 1 f�vr. 2013, 14:40:27
 *  \author cec
 */

#ifndef ABS_HPP_
#define ABS_HPP_

#include "ssc/functors_for_optimizer/Unary.hpp"

namespace ssc
{
    namespace functors_for_optimizer
    {
        class Abs : public Unary
        {
            public:
                Abs(const NodePtr& n_);
                std::string get_operator_name() const;
                NodePtr diff(const StatePtr& state) const;
                NodePtr clone() const;
                bool is_null() const;
                std::string get_type() const;
                void update_lambda();
                void accept(NodeVisitor& v) const;
        };

        typedef TR1(shared_ptr)<Abs> AbsPtr;
    }
}

#endif /* ABS_HPP_ */
