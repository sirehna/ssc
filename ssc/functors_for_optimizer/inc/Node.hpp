#ifndef __NODEHPP__
#define __NODEHPP__

#include <functional>
#include <tr1/memory>

class Node;

class State;
typedef std::tr1::shared_ptr<Node> NodePtr;
typedef std::tr1::shared_ptr<State> StatePtr;

class NodeVisitor;

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
        virtual bool is_null() const;

    protected:
        double lambda;
        std::function<double()> value;
};

#endif

