#ifndef __POWHPP__
#define __POWHPP__

#include "Binary.hpp"

class Pow : public Binary
{
    public:
        Pow(const NodePtr& n1, const NodePtr& n2);
        Pow(const NodePtr& n1, const double& n2);
        NodePtr diff(const StatePtr& state) const;
        std::string get_operator_name() const;
        NodePtr clone() const;

    private:
        std::function<double()> get_pow_fun() const;
};

typedef std::tr1::shared_ptr<Pow> PowPtr;

#endif
