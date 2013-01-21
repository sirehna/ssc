#include "Fx.hpp"
#include "State.hpp"

Grad Fx::grad() const
{
    return Fx_grad;
}

Hes Fx::hes() const
{
    return Fx_hes;
}



Fx::Fx(const std::vector<std::tr1::shared_ptr<Thruster> >& thrusters_) : thrusters(thrusters_),
Fx_val(std::vector<ValType>()),
Fx_grad(Grad()),
Fx_hes(Hes())
{
    for (const auto t:thrusters)
    {
        Fx_val.push_back(t->get_Fx());
        auto indexes = get_idx(t->get_states());
        Fx_grad.idx.insert(Fx_grad.idx.end(), indexes.begin(), indexes.end());
        auto grad = t->get_grad_Fx();
        Fx_grad.values.insert(Fx_grad.values.end(), grad.begin(), grad.end()); 
    }
}

ValType Fx::val() const
{
    auto ret = [&]() -> double
    {
        double v = 0;
        for (auto it = Fx_val.begin() ; it != Fx_val.end() ; ++it)
        {
            v += (*it)();
        }
        return v;
    };
    return ret;
}

std::vector<size_t> Fx::get_idx(const StateList& states) const
{
    std::vector<size_t> ret;
    for (auto s:states) ret.push_back(s->get_index());
    return ret;
}


