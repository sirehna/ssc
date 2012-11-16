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

class TwoDimensionalInterpolationException : public Exception
{
    public:
        TwoDimensionalInterpolationException(const char* s) :
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
#include "test_macros.hpp"
template <typename T> class TwoDimensionalInterpolation
{
    public:
        TwoDimensionalInterpolation(const double& xmin, const double& xmax, const double& ymin_, const double& ymax_, const std::vector<std::vector<double> >& val) : interpolators(std::vector<std::tr1::shared_ptr<T> >()),
        ymin(ymin_),
        ymax(ymax_)
        {
            if (val.size() < 2)
            {
                THROW("TwoDimensionalInterpolation::TwoDimensionalInterpolation(const double&, const double&, const double&, const double&, const std::vector<std::vector<double>>&)", TwoDimensionalInterpolationException, "val must contain at least two vectors");
            }
            const size_t n = val.front().size();
            for (auto it = val.begin() ; it != val.end() ; ++it)
            {
                if (it->size() != n)
                {
                    THROW("TwoDimensionalInterpolation::TwoDimensionalInterpolation(const double&, const double&, const double&, const double&, const std::vector<std::vector<double>>&)", TwoDimensionalInterpolationException, "Not all vectors in val have the same number of elements");
                }
                if (it->size()<2)
                {
                    THROW("TwoDimensionalInterpolation::TwoDimensionalInterpolation(const double&, const double&, const double&, const double&, const std::vector<std::vector<double>>&)", TwoDimensionalInterpolationException, "At least one vector in val has fewer than 2 elements");
                }
                interpolators.push_back(std::tr1::shared_ptr<T>(new T(xmin, xmax, *it)));
            }
        }

        double f(const double& x, const double& y)
        {
            std::vector<double> interpolated_values_for_x_fixed;
            for (auto it = interpolators.begin() ; it != interpolators.end() ; ++it)
            {
                (*it)->set_computed_value(y);
                interpolated_values_for_x_fixed.push_back((*it)->f());
            }
            T final_interpolation(ymin,ymax,interpolated_values_for_x_fixed);
            final_interpolation.set_computed_value(x);
            return final_interpolation.f();
        }
    private:
        TwoDimensionalInterpolation();
        std::vector<std::tr1::shared_ptr<T> > interpolators;
        double ymin;
        double ymax;
};

#endif /* TWODIMENSIONALSPLINES_HPP_ */
