#ifndef __POWHPP__
#define __POWHPP__

#include "ssc/functors_for_optimizer/Binary.hpp"


class Pow : public Binary
{
    public:
        Pow(const NodePtr& n1, const NodePtr& n2);
        Pow(const NodePtr& n1, const double& n2);
        NodePtr diff(const StatePtr& state) const;
        std::string get_operator_name() const;
        NodePtr clone() const;
        bool is_null() const;
        bool equals(const Node& rhs) const;
        using Node::equals_derived;
        bool equals_derived(const Pow& rhs) const;
        std::string get_type() const;
        NodePtr simplify() const;
        void update_lambda();
        bool is_constant() const;
    private:
        std::function<double()> get_pow_fun() const;
};

typedef std::tr1::shared_ptr<Pow> PowPtr;

#endif
