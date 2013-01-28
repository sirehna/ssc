/*
 * Multiply.cpp
 *
 * \date 23 janv. 2013, 08:29:31
 *  \author cec
 */

#include "Multiply.hpp"
#include "test_macros.hpp"
#include "NodeAbstractVisitor.hpp"
#include <algorithm>

#define MAX(a,b) a>b ? a : b

Multiply::Multiply(const Node& n1_, const Node& n2_) :
children(std::vector<std::tr1::shared_ptr<Node> >()),
v(std::vector<ValType>({n1_.val(),n2_.val()})),
dv(std::vector<Grad>({n1_.grad(),n2_.grad()})),
d2v(std::vector<Hes>({n1_.hes(),n2_.hes()})),
f(ValType([&v]()->double {return v.at(0)()*v.at(1)();})),
df(calculate_df(n1_,n2_)),
d2f(Hes())
{
    children.push_back(std::tr1::shared_ptr<Node>(n1_.clone()));
    children.push_back(std::tr1::shared_ptr<Node>(n2_.clone()));
}

Grad Multiply::calculate_df(const Node& A, const Node& B) const
{
    size_t ka = 0;
    size_t kb = 0;
    size_t kc = 0;
    Grad C;

    auto grad_A_idx = A.grad().idx;
    auto grad_B_idx = B.grad().idx;
    const size_t idx_max_A = *std::max_element(grad_A_idx.begin(), grad_A_idx.end());
    const size_t idx_max_B = *std::max_element(grad_B_idx.begin(), grad_B_idx.end());

    C.idx = std::vector<size_t>(MAX(idx_max_A,idx_max_B)+1,0);
    C.values = std::vector<ValType>(MAX(idx_max_A,idx_max_B)+1, ValType());


    auto valA = A.val();
    auto valB = B.val();
    for(;(ka<grad_A_idx.size())&&(kb<grad_B_idx.size());)
    {
        auto dfA = A.grad().values.at(ka);
        auto dfB = B.grad().values.at(kb);
        if (grad_A_idx.at(ka) < grad_B_idx.at(kb))
        {
            C.idx.at(kc)    = grad_A_idx.at(ka);
            C.values.at(kc) = ValType([valB,dfA]()->double {return dfA()*valB();});
            ++ka;
        }
        else if (grad_A_idx.at(ka) == grad_B_idx.at(kb))
        {
            C.idx.at(kc)    = A.grad().idx.at(ka);
            C.values.at(kc) = ValType([valA,valB,dfA,dfB]()->double {return dfA()*valB() + valA()*dfB();});
            ++ka;
            ++kb;
        }
        else
        {
            C.idx.at(kc)    = grad_B_idx.at(kb);
            C.values.at(kc) = ValType([valA,dfB]()->double {return dfB()*valA();});
            ++kb;
        }
        ++kc;
    }
    fetch_extra_elements_if_vectors_have_different_nb_of_elements(ka, A, B, kc, C);
    fetch_extra_elements_if_vectors_have_different_nb_of_elements(kb, B, A, kc, C);
    return C;
}
#include "NodeSerializationVisitor.hpp"

void Multiply::fetch_extra_elements_if_vectors_have_different_nb_of_elements(size_t& k, const Node& A, const Node& B, size_t& kc, Grad& C) const
{
    auto grad_A_idx = A.grad().idx;
    auto valB = B.val();
    COUT(k);
    COUT(grad_A_idx.size());
    COUT(A);
    COUT(B);
    for (;k<grad_A_idx.size();++k,++kc)
    {
        auto dfA = A.grad().values.at(k);
        COUT(kc);
        COUT(C.idx.size());
        COUT(C.values.size());
        C.idx.at(kc)    = grad_A_idx.at(k);
        C.values.at(kc) = ValType([valB,dfA]()->double {return dfA()*valB();});
    }
}

/*
Multiply::Multiply(const Multiply& n1_, const Node& n2_) :
        v(n1_.v),
        dv(n1_.dv),
        d2v(n1_.d2v),
        f(ValType()),
        df(Grad()),
        d2f(Hes())
{
    v.push_back(n2_.val());
    f = ValType([v]()->double
        {
            double ret = 1;
            for (auto ff = v.begin() ; ff != v.end() ; ++ff)
            {
                ret *= (*ff)();
            }
            return ret;
        });
}
Multiply::Multiply(const Node& n1_, const Multiply& n2_) :
        v(n2_.v),
        dv(n2_.dv),
        d2v(n2_.d2v),
        f(ValType()),
        df(Grad()),
        d2f(Hes())
{
    v.push_back(n1_.val());
    f = ValType([v]()->double
        {
            double ret = 1;
            for (auto ff = v.begin() ; ff != v.end() ; ++ff)
            {
                ret *= (*ff)();
            }
            return ret;
        });
}

Multiply::Multiply(const Multiply& n1_, const Multiply& n2_) :
        v(n1_.v),
        dv(n1_.dv),
        d2v(n1_.d2v),
        f(ValType()),
        df(Grad()),
        d2f(Hes())
{
    v.insert(v.end(), n2_.v.begin(), n2_.v.end());
    f = ValType([v]()->double
        {
            double ret = 1;
            for (auto ff = v.begin() ; ff != v.end() ; ++ff)
            {
                ret *= (*ff)();
            }
            return ret;
        });
}
*/
ValType Multiply::val() const
{
    return f;
}

Grad Multiply::grad() const
{
    return df;
}

Hes Multiply::hes() const
{
    return Hes();
}

void Multiply::accept(NodeAbstractVisitor& v) const
{
    v.visit(*this);
}

std::vector<std::tr1::shared_ptr<Node> > Multiply::get_children() const
{
    return children;
}

Node* Multiply::clone() const
{
    return new Multiply(*this);
}
