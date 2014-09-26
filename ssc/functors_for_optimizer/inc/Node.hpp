#ifndef __NODEHPP__
#define __NODEHPP__

#include "tr1_macros.hpp"
#include <functional>
#include TR1INC(memory)
#include <map>
#include <vector>

class Node;

class State;
typedef std::tr1::shared_ptr<Node> NodePtr;
typedef std::tr1::shared_ptr<State> StatePtr;

typedef std::map<NodePtr,NodePtr> FactorMap;

class NodeVisitor;

class Constant;
class Difference;
class N_ary;
class Null;
class Multiply;
class Parameter;
class State;
class Pow;
class Divide;
class Unary;
#include <string>
class Node
{
    public:
        Node();
        virtual ~Node() {}
        std::function<double()> get_lambda() const;
        virtual NodePtr diff(const StatePtr& state) const = 0;
        void multiply_by(const double& k);
        virtual void accept(NodeVisitor& v) const = 0;
        virtual NodePtr clone() const  = 0;
        virtual bool is_null() const = 0;
        bool equals_one() const;
        virtual bool is_constant() const;
        virtual bool is_negative() const;

        virtual bool equals(const Node& rhs) const = 0;
        virtual bool equals_derived(const Constant& rhs) const;
        virtual bool equals_derived(const Difference& rhs) const;
        virtual bool equals_derived(const N_ary& rhs) const;
        virtual bool equals_derived(const Null& rhs) const;
        virtual bool equals_derived(const Parameter& rhs) const;
        virtual bool equals_derived(const Pow& rhs) const;
        virtual bool equals_derived(const Divide& rhs) const;
        virtual bool equals_derived(const Unary& rhs) const;
        virtual bool equals_derived(const State& rhs) const;


        virtual std::string get_type() const = 0;

        virtual NodePtr simplify() const;
        virtual FactorMap get_factors_with_exponents() const;
        virtual std::vector<NodePtr> get_factors() const;
        virtual std::vector<NodePtr> get_operands() const;
        double get_multiplicative_factor() const;
        virtual bool must_parenthesize() const;
        virtual void update_lambda() = 0;

    protected:
        double factor;
        std::function<double()> value;
};

#endif

