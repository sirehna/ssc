/*
 * count_states_and_parameters.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: cady
 */

#include <algorithm>

#include "count_states_and_parameters.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"
#include "ssc/functors_for_optimizer/Binary.hpp"
#include "ssc/functors_for_optimizer/N_ary.hpp"
#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/functors_for_optimizer/Null.hpp"
#include "ssc/functors_for_optimizer/Unary.hpp"
#include "ssc/functors_for_optimizer/Constant.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/functors_for_optimizer/Sum.hpp"

class CounterVisitor : public ssc::functors_for_optimizer::NodeVisitor
{
    public:
        CounterVisitor() : max_idx(0) {}
        void visit(const ::ssc::functors_for_optimizer::Binary& node)
        {
            node.get_lhs()->accept(*this);
            node.get_rhs()->accept(*this);
        }
        void visit(const ::ssc::functors_for_optimizer::Sum& node)
        {
            auto sons = node.get_sons();
            for( size_t i = 0 ; i < sons.size() ; ++i)
            {
                sons[i]->accept(*this);
            }
        }
        void visit(const ::ssc::functors_for_optimizer::Multiply& node)
        {
            auto sons = node.get_sons();
            for( size_t i = 0 ; i < sons.size() ; ++i)
            {
                sons[i]->accept(*this);
            }
        }
        void visit(const ::ssc::functors_for_optimizer::State& node)
        {
            max_idx = std::max(max_idx, node.get_index());
        }

        void visit(const ::ssc::functors_for_optimizer::Parameter& ) {}
        void visit(const ::ssc::functors_for_optimizer::Constant& ) {}
        void visit(const ::ssc::functors_for_optimizer::Null& ) {}
        void visit(const ::ssc::functors_for_optimizer::Unary& node)
        {
            auto son = node.get_son();
            son->accept(*this);
        }

        size_t get_max_state_index() const
        {
            return max_idx;
        }

    private:
        size_t max_idx;
};


size_t ssc::functors_for_optimizer::max_state_index(const NodePtr& node)
{
    CounterVisitor visitor;
    node->accept(visitor);
    return visitor.get_max_state_index();
}
