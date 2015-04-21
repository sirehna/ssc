/*
 * Binary.hpp
 *
 * \date 31 janv. 2013, 16:06:42
 *  \author cec
 */

#ifndef NARY_HPP_
#define NARY_HPP_

#include "ssc/functors_for_optimizer/Node.hpp"
#include <string>
#include <vector>
#include <map>

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/BinaryTest.cpp BinaryTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/BinaryTest.cpp BinaryTest expected output
 */

class N_ary : public Node
{
    public:
        N_ary(const NodePtr& n1, const NodePtr& n2);
        N_ary(const std::vector<NodePtr>& nodes);
        ~N_ary() {}
        std::vector<NodePtr> get_sons() const;
        virtual std::string get_operator_name() const = 0;
        bool equals(const Node& rhs) const;
        using Node::equals_derived;
        bool equals_derived(const N_ary& rhs) const;
        bool equals_derived(const Constant& rhs) const;
        void update_lambda();
        bool is_constant() const;

    protected:
        virtual void common_build() = 0;
        std::vector<NodePtr> sons;
        void set_value(const std::function<double()>& val);
        std::vector<NodePtr> extract_subnodes(const std::function<std::vector<NodePtr>(const NodePtr& n)>& extractor);
        std::map<NodePtr, size_t> get_occurence_of_each_factor() const;
        std::vector<NodePtr> group_constants_together(const std::vector<NodePtr>& nodes, const std::function<double(double,double)>& f) const;
    private:
        N_ary();
};

#endif /* ARY_HPP_ */
