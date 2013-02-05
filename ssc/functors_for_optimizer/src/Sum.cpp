/*
 * Sum.cpp
 *
 * \date 31 janv. 2013, 16:05:53
 *  \author cec
 */

#include "Sum.hpp"
#include "NodeVisitor.hpp"

Sum::Sum(const NodePtr& n1, const NodePtr& n2) : N_ary(n1,n2)
{
    if (n1->is_null()) sons.erase (sons.begin());
    if (n2->is_null()) sons.erase (sons.begin()+1);

    set_value([sons,&lambda]()->double
              {
                  double ret = 0;
                  for (auto son = sons.begin() ; son != sons.end() ; ++son)
                  {
                      ret += (*son)->get_value()();
                  }
                    return lambda*ret;
               });
}

Sum::Sum(const std::vector<NodePtr>& nodes) : N_ary(nodes)
{

}

NodePtr Sum::diff(const StatePtr& state) const
{
    std::vector<NodePtr> dsons;
    for (auto son = sons.begin() ; son != sons.end() ; ++son)
    {
        dsons.push_back((*son)->diff(state));
    }
    return NodePtr(new Sum(dsons));
}

std::string Sum::get_operator_name() const
{
    return "+";
}

NodePtr Sum::clone() const
{
    return NodePtr(new Sum(*this));
}
