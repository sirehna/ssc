#ifndef __PARAMETER_HPP__
#define __PARAMETER_HPP__

#include <tr1/memory> // For shared_ptr
typedef std::tr1::shared_ptr<double> SharedPtr;
#include "Node.hpp"



class Parameter : public Node
{
    public:
          Parameter(const double& v);
          bool operator==(const Parameter& rhs) const;
          bool operator!=(const Parameter& rhs) const;
          virtual ~Parameter();
          ValType val() const;
          virtual Grad grad() const;
          virtual Hes hes() const;

    protected:
        SharedPtr ptr;
        Grad df;
        Hes d2f;

    private:
        Parameter();
        ValType f;

    friend double& operator*(const Parameter& s);
};

double& operator*(const Parameter& s);

#endif
