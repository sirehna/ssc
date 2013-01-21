#include "Pow.hpp"
#include <cmath>
#include "State.hpp"
#include "StateNode.hpp"

#include <iostream>
#define QUOTE_ME(a) #a
#define QUOTE(a) QUOTE_ME(a)
#define COUT(a) std::cout << "in file " << __FILE__ << ", line " << __LINE__ << ": " << QUOTE(a) << " = " << a << std::endl;
Pow::Pow(const Node& n_, const double& exponent) :
s(n_.val()),
ds(n_.grad()),
d2s(n_.hes()),
s_power_e([&]()->double {return pow(s(),exponent);}),
ds_power_e(Grad()),
d2s_power_e(Hes())
{
    ds_power_e.idx = ds.idx;
    for (auto f:ds.values)
    {
        const auto df = [&]()->double
                        {
                            COUT(exponent);
                            COUT(s());
                            //COUT(f());
                            return exponent*pow(s(),exponent-1.);
                        };
        ds_power_e.values.push_back(df);
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

