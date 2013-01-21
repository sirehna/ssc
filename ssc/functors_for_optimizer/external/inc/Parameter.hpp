#ifndef __PARAMETER_HPP__
#define __PARAMETER_HPP__

#include <tr1/memory> // For shared_ptr

typedef std::tr1::shared_ptr<double> SharedPtr;

class Parameter
{
    public:
        Parameter(const double& v);
          bool operator==(const Parameter& rhs) const;
          bool operator!=(const Parameter& rhs) const;
          virtual ~Parameter();

    private:
        Parameter();

    protected:
        SharedPtr ptr;

    friend double& operator*(const Parameter& s);
};

double& operator*(const Parameter& s);

#endif
