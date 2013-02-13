#ifndef __NODEHPP__
#define __NODEHPP__

#include <functional>
#include <tr1/memory>

class Node;

class State;
typedef std::tr1::shared_ptr<Node> NodePtr;
typedef std::tr1::shared_ptr<State> StatePtr;

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
        std::function<double()> get_value() const;
        virtual NodePtr diff(const StatePtr& state) const = 0;
        void multiply_by(const double& k);
        virtual void accept(NodeVisitor& v) const = 0;
        virtual NodePtr clone() const  = 0;
        virtual bool is_null() const = 0;

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

        virtual NodePtr simplify() const = 0;

    protected:
        double lambda;
        std::function<double()> value;
};

#endif

