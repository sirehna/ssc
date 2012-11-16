/*
 * TwoDimensionalSplines.cpp
 *
 * \date 13 nov. 2012, 16:50:26
 *  \author cec
 */

#include "TwoDimensionalInterpolation.hpp"
#include "ParabolicRunoutSplines.hpp"


TwoDimensionalSplines::TwoDimensionalSplines(const std::vector<double>& x,
        const std::vector<double>& y,
        const std::vector<std::vector<double> >& val) :
        splines(std::vector<std::tr1::shared_ptr<ParabolicRunoutSplines> >())
{
    if (x.size()) {}
    if (y.size()) {}
    if (val.size()) {}
}

double TwoDimensionalSplines::f(const double& x, const double& y)
{
    return x*x+y*y;
}
