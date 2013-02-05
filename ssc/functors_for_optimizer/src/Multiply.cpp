/*
 * Multiply.cpp
 *
 * \date 23 janv. 2013, 08:29:31
 *  \author cec
 */

#include "Multiply.hpp"
#include "Sum.hpp"
#include "NodeVisitor.hpp"

#include "test_macros.hpp"

Multiply::Multiply(const NodePtr& n1, const NodePtr& n2) : N_ary(n1,n2)
{
    COUT("");
    if (n1->is_null()) sons.clear();
    COUT("");
    if (n2->is_null()) sons.clear();
    COUT("");
    set_value([sons,&lambda]()->double
              {
                  double ret = 1;
                  for (auto son = sons.begin() ; son != sons.end() ; ++son)
                  {
                      ret *= (*son)->get_value()();
                  }
                    return lambda*ret;
               });
}

Multiply::Multiply(const std::vector<NodePtr>& nodes) : N_ary(nodes)
{

}

NodePtr Multiply::diff(const StatePtr& state) const
{
    std::vector<NodePtr> dsons;
    const size_t n = sons.size();
    for (size_t i = 0 ; i < n ; ++i)
    {
        std::vector<NodePtr> prod;
        for (size_t j = 0 ; j < n ; ++j)
        {
            COUT("");
            if (i != j) prod.push_back(sons.at(j));
            COUT("");
        }
        COUT("");
        prod.push_back(sons.at(i)->diff(state));
        COUT("");
        dsons.push_back(NodePtr(new Multiply(prod)));
    }
    return NodePtr(new Sum(dsons));
}

std::string Multiply::get_operator_name() const
{
    return "*";
}

NodePtr Multiply::clone() const
{
    return NodePtr(new Multiply(*this));
}
