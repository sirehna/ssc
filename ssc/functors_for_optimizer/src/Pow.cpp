#include "Pow.hpp"
#include <cmath>
#include "State.hpp"
#include "test_macros.hpp"
#include <iostream>
Pow::Pow(const Node& n_, const double& exponent) :
s(n_.val()),
ds(n_.grad()),
d2s(n_.hes()),
s_power_e([&]()->double {return pow(s(),exponent);}),
ds_power_e(Grad()),
d2s_power_e(Hes())
{
    ds_power_e.idx = ds.idx;
    for (auto ds_dx = ds.values.begin() ; ds_dx != ds.values.end() ; ++ds_dx)
    {
        const auto df = [&,ds_dx]()->double
                        {
                            return exponent*pow(s(),exponent-1.)*(*ds_dx)();
                        };
        ds_power_e.values.push_back(ValType(df));
    }
}

ValType Pow::val() const
{

    return s_power_e;
}

Grad Pow::grad() const
{
    return ds_power_e;
}

Hes Pow::hes() const
{
    return Hes();
}

