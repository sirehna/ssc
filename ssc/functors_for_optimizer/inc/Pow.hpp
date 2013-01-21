#ifndef __POWHPP__
#define __POWHPP__
#include <tr1/memory>
#include "Node.hpp"
class State;
class StateNode;
class Pow : public Node
{
    public:
        Pow(const Node& node, const double& exponent);
        ValType val() const;
        Grad grad() const;
        Hes hes() const;
    private:
        ValType s;
        Grad ds;
        Hes d2s;
        
        ValType s_power_e;
        Grad ds_power_e;
        Hes d2s_power_e;
};

#endif
