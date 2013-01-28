#include "Pow.hpp"
#include <cmath>
#include "State.hpp"
#include "test_macros.hpp"
#include "NodeAbstractVisitor.hpp"
#include <iostream>
#include <map>

Pow::Pow(const Node& n_, const double& exponent) :
s(n_.val()),
ds(n_.grad()),
d2s(n_.hes()),
s_power_e([&]()->double {return pow(s(),exponent);}),
ds_power_e(Grad()),
d2s_power_e(Hes()),
child(std::tr1::shared_ptr<Node>(n_.clone())),
exponent_(exponent)
{
    ds_power_e.idx = ds.idx;
    const size_t n = ds.values.size();
    typedef std::pair<size_t,size_t> IdxPair;
    std::map<IdxPair, ValType > ij2val;
    const size_t p = d2s.values.size();
    for (size_t i = 0 ; i < n ; ++i)
    {
        for (size_t j = 0 ; j < n ; ++j)
        {
            for (size_t k = 0 ; k < p ; ++k)
            {
                const size_t d2s_i = d2s.row_idx.at(k);
                const size_t d2s_j = d2s.col_idx.at(k);
                if ((d2s_i==ds.idx.at(i)) && (d2s_j==ds.idx.at(k)))
                {
                    ij2val[std::make_pair(i,j)] = d2s.values.at(k);
                }
            }
        }
    }
    for (size_t i = 0 ; i < n ; ++i)
    {
        auto ds_dxi = ds.values.at(i);
        const auto df = [&,ds_dxi]()->double
                        {
                            return exponent*pow(s(),exponent-1.)*ds_dxi();
                        };
        ds_power_e.values.push_back(ValType(df));
        for (size_t j = 0 ; j < n ; ++j)
        {
            auto ds_dxj = ds.values.at(j);
            auto ij = std::make_pair(i,j);
            ValType d2s_dxidxj;
            if (ij2val.find(ij) != ij2val.end())
            {
                d2s_dxidxj = ij2val[ij];
            }
            const auto d2f = [&,ds_dxi,ds_dxj,d2s_dxidxj]()->double
                            {
                                return exponent*(exponent-1.)*pow(s(),exponent-2.)*ds_dxi()*ds_dxj()
                                       + exponent*pow(s(),exponent-1.)*d2s_dxidxj();
                            };
            d2s_power_e.row_idx.push_back(ds.idx.at(i));
            d2s_power_e.col_idx.push_back(ds.idx.at(j));
            d2s_power_e.values.push_back(ValType(d2f));
        }
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
    return d2s_power_e;
}

void Pow::accept(NodeAbstractVisitor& v) const
{
    v.visit(*this);
}

Node* Pow::clone() const
{
    return new Pow(*this);
}

std::tr1::shared_ptr<Node> Pow::get_child() const
{
    return child;
}

double Pow::get_exponent() const
{
    return exponent_;
}
