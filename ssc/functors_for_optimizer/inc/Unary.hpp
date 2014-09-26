/*
 * Unary.hpp
 *
 * \date 1 févr. 2013, 12:33:33
 *  \author cec
 */

#ifndef UNARY_HPP_
#define UNARY_HPP_

#include "Node.hpp"


class Unary : public Node
{

    public:
        Unary(const NodePtr& n_);
        NodePtr get_son() const;
        void accept(NodeVisitor& v) const;
        virtual std::string get_operator_name() const = 0;
        bool equals(const Node& n_) const;
        using Node::equals_derived;
        virtual bool equals_derived(const Unary& rhs) const;
        bool is_constant() const;
    protected:
        NodePtr n;
        void set_value(const std::function<double()>& val);
    private:
        Unary();
};


#endif /* UNARY_HPP_ */
