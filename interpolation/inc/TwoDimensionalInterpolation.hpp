/*
 * TwoDimensionalSplines.hpp
 *
 * \date 13 nov. 2012, 16:50:25
 *  \author cec
 */
#include <vector>
#include <tr1/memory>

class ParabolicRunoutSplines;
#ifndef TWODIMENSIONALSPLINES_HPP_
#define TWODIMENSIONALSPLINES_HPP_

#include "Exception.hpp"

class TwoDimensionalSplinesException : public Exception
{
    public:
        TwoDimensionalSplinesException(const char* s) :
                Exception(s)
        {
        }
};

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet splines/unit_tests/src/TwoDimensionalSplinesTest.cpp TwoDimensionalSplinesTest example
 *  \section ex2 Expected output
 *  \snippet splines/unit_tests/src/TwoDimensionalSplinesTest.cpp TwoDimensionalSplinesTest expected output
 */

class TwoDimensionalSplines
{
    public:
        TwoDimensionalSplines(const std::vector<double>& x, const std::vector<double>& y, const std::vector<std::vector<double> >& val);
        double f(const double& x, const double& y);
    private:
        TwoDimensionalSplines();
        std::vector<std::tr1::shared_ptr<ParabolicRunoutSplines> > splines;
};

#endif /* TWODIMENSIONALSPLINES_HPP_ */
