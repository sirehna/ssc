/*
 * count_states_and_parameters.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: cady
 */

#include <algorithm>

#include "ssc/functors_for_optimizer/StateAndParameterCounter.hpp"
#include "ssc/functors_for_optimizer/NodeVisitor.hpp"
#include "ssc/functors_for_optimizer/Binary.hpp"
#include "ssc/functors_for_optimizer/N_ary.hpp"
#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/functors_for_optimizer/Null.hpp"
#include "ssc/functors_for_optimizer/Sin.hpp"
#include "ssc/functors_for_optimizer/Cos.hpp"
#include "ssc/functors_for_optimizer/Ln.hpp"
#include "ssc/functors_for_optimizer/PiecewiseConstantFunctor.hpp"
#include "ssc/functors_for_optimizer/PiecewiseLinearFunctor.hpp"
#include "ssc/functors_for_optimizer/PiecewiseParabolicFunctor.hpp"
#include "ssc/functors_for_optimizer/SplineFunctor.hpp"
#include "ssc/functors_for_optimizer/Constant.hpp"
#include "ssc/functors_for_optimizer/Multiply.hpp"
#include "ssc/functors_for_optimizer/Sum.hpp"



class CounterVisitor : public ssc::functors_for_optimizer::NodeVisitor
{
    public:
        CounterVisitor() : max_state_idx(0), max_parameter_idx(0),states_present(false), parameters_present(false) {}
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
            states_present = true;
            max_state_idx = std::max(max_state_idx, node.get_index());
        }

        void visit(const ::ssc::functors_for_optimizer::Parameter& node)
        {
            parameters_present = true;
            max_parameter_idx = std::max(max_parameter_idx, node.get_index());
        }

        void visit(const ::ssc::functors_for_optimizer::Constant& ) {}
        void visit(const ::ssc::functors_for_optimizer::Null& ) {}
        void visit(const ::ssc::functors_for_optimizer::Sin& node)
        {
            auto son = node.get_son();
            son->accept(*this);
        }
        void visit(const ::ssc::functors_for_optimizer::Cos& node)
        {
            auto son = node.get_son();
            son->accept(*this);
        }
        void visit(const ::ssc::functors_for_optimizer::Ln& node)
        {
            auto son = node.get_son();
            son->accept(*this);
        }
        void visit(const ::ssc::functors_for_optimizer::PiecewiseConstantFunctor& node)
        {
            auto son = node.get_son();
            son->accept(*this);
        }
        void visit(const ::ssc::functors_for_optimizer::PiecewiseLinearFunctor& node)
        {
            auto son = node.get_son();
            son->accept(*this);
        }
        void visit(const ::ssc::functors_for_optimizer::PiecewiseParabolicFunctor& node)
        {
            auto son = node.get_son();
            son->accept(*this);
        }
        void visit(const ::ssc::functors_for_optimizer::SplineFunctor& node)
        {
            auto son = node.get_son();
            son->accept(*this);
        }

        size_t get_max_state_index() const
        {
            return max_state_idx;
        }

        size_t get_max_parameter_index() const
        {
            return max_parameter_idx;
        }

        bool there_are_states() const
        {
            return states_present;
        }

        bool there_are_parameters() const
        {
            return parameters_present;
        }

    private:
        size_t max_state_idx;
        size_t max_parameter_idx;
        bool states_present;
        bool parameters_present;
};

class ssc::functors_for_optimizer::StateAndParameterCounter::Impl
{
    public:
        Impl(const NodePtr& node) : visitor()
        {
            node->accept(visitor);
        }

        CounterVisitor visitor;
    private:
        Impl();// Disabled


};

ssc::functors_for_optimizer::StateAndParameterCounter::StateAndParameterCounter(const NodePtr& node) : pimpl(new Impl(node))
{}


size_t ssc::functors_for_optimizer::StateAndParameterCounter::max_state_index() const
{
    return pimpl->visitor.get_max_state_index();
}

size_t ssc::functors_for_optimizer::StateAndParameterCounter::max_parameter_index() const
{
    return pimpl->visitor.get_max_parameter_index();
}

bool ssc::functors_for_optimizer::StateAndParameterCounter::there_are_states() const
{
    return pimpl->visitor.there_are_states();
}

bool ssc::functors_for_optimizer::StateAndParameterCounter::there_are_parameters() const
{
    return pimpl->visitor.there_are_parameters();
}
