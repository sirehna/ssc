#include "Node.hpp"

class State;
class StateNode : public Node
{
    public:
        StateNode(const State& state);
        ValType val() const;
        Grad grad() const;
        Hes hes() const;
    private:
        StateNode();
        ValType f;
        Grad df;
        Hes d2f;
};
