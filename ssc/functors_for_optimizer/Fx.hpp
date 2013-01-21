#ifndef __FXHPP__
#define __FXHPP__

#include <tr1/memory>
#include "Node.hpp"
#include "Thruster.hpp"

class Fx : public Node
{
    public:
        Fx(const std::vector<std::tr1::shared_ptr<Thruster> >& thrusters_);
        ValType val() const;
        Grad grad() const;
        Hes hes() const;

    private:
        std::vector<size_t> get_idx(const StateList& states) const;
        Fx();
        std::vector<std::tr1::shared_ptr<Thruster> > thrusters;
        std::vector<ValType> Fx_val;
        Grad Fx_grad;
        Hes Fx_hes;
};
#endif
