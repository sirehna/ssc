/*
 * MinimizeSpline.hpp
 *
 * \date 10 juin 2013, 11:48:50
 *  \author cec
 */

#ifndef MINIMIZESPLINE_HPP_
#define MINIMIZESPLINE_HPP_

#include <tr1/memory>
#include <vector>

/** \author cec
 *  \ingroup optimizer
 *  \brief Find the minimum of a function defined by a set of (x,y) pairs
 *  \details Given xmin, xmax & a vector of doubles, calculates the position x0
 *   of the minimum using IPOPT initialized at the lowest given point (x
 *   corresponding to min(y)).
 *  \section ex1 Example
 *  \snippet optimizer/unit_tests/src/MinimizeSplineTest.cpp MinimizeSplineTest example
 *  \section ex2 Expected output
 *  \snippet optimizer/unit_tests/src/MinimizeSplineTest.cpp MinimizeSplineTest expected output
 */

class MinimizeSpline
{
    public:
        MinimizeSpline(double xmin, double xmax, const std::vector<double>& y);
        double get_min();
    private:
        class Impl;
        std::tr1::shared_ptr<Impl> pimpl;
        MinimizeSpline();
};

#endif /* MINIMIZESPLINE_HPP_ */
