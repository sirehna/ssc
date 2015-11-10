/*
 * Multiply.hpp
 *
 * \date 23 janv. 2013, 08:29:31
 *  \author cec
 */

#ifndef MULTIPLY_HPP_
#define MULTIPLY_HPP_
#include "ssc/functors_for_optimizer/N_ary.hpp"

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/MultiplyTest.cpp MultiplyTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/MultiplyTest.cpp MultiplyTest expected output
 */

namespace ssc
{
    namespace functors_for_optimizer
    {
        class Multiply : public N_ary
        {
            public:
                Multiply(const NodePtr& n1, const NodePtr& n2);
                Multiply(const std::vector<NodePtr>& nodes);
                NodePtr diff(const StatePtr& state) const;
                std::string get_operator_name() const;
                NodePtr clone() const;
                bool is_null() const;
                std::string get_type() const;
                NodePtr simplify() const;
                std::vector<NodePtr> get_factors() const;
                FactorMap get_factors_with_exponents() const;
                void accept(NodeVisitor& v) const;
                void update_lambda();

            private:
                void common_build();
                void remove_ones_and_zeros();
                bool null_or_one(const NodePtr& node) const;
                std::vector<NodePtr> group_factors_together() const;
        };

        typedef TR1(shared_ptr)<Multiply> Mult;
        FactorMap operator+(const FactorMap& a, const FactorMap& b);
    }
}
#endif /* MULTIPLY_HPP_ */
