/*
 * LinearInterpolationVariableStep.cpp
 *
 * \date 10 avr. 2013, 12:54:12
 *  \author cec
 */

#include "LinearInterpolationVariableStep.hpp"
#include "PiecewiseConstantVariableStep.hpp"

class Linear
{
    public:
        Linear() : slope(0), intersection_with_origin(0)
        {
        }

        Linear(const double& slope_, const double& intersection_with_origin_) : slope(slope_), intersection_with_origin(intersection_with_origin_)
        {
        }

        double slope;
        double intersection_with_origin;
};

std::vector<Linear> compute_linear_coefficients(const std::vector<double>& x, const std::vector<double>& y);
std::vector<Linear> compute_linear_coefficients(const std::vector<double>& x, const std::vector<double>& y)
{
    const size_t n = x.size();
    std::vector<Linear> ret;
    PiecewiseConstantVariableStep<double>(x,y); // Checks if x is in strictly increasing order & that x & y have same size
    for (size_t i = 0 ; i < n-1 ; ++i)
    {
        const double a = (y.at(i+1) - y.at(i)) / (x.at(i+1) - x.at(i));
        const double b = y.at(i) - a*x.at(i);
        ret.push_back(Linear(a,b));
    }
    ret.push_back(ret.back());
    return ret;
}

class LinearInterpolationVariableStep::LinearInterpolationVariableStepImpl
{
    public:
        LinearInterpolationVariableStepImpl(const std::vector<double>& x, const std::vector<double>& y) : coeff(PiecewiseConstantVariableStep<Linear>(x, compute_linear_coefficients(x,y))), current_coeff(Linear()), x0_(0)
        {

        }

        void set_computed_value(const double& x0)
        {
            x0_ = x0;
            coeff.set_computed_value(x0);
            current_coeff = coeff.f();
        }

        double get_val() const
        {
            return current_coeff.slope*x0_ + current_coeff.intersection_with_origin;
        }

        double get_derivative() const
        {
            return current_coeff.slope;
        }

    private:
        LinearInterpolationVariableStepImpl();
        PiecewiseConstantVariableStep<Linear> coeff;
        Linear current_coeff;
        double x0_;
};


LinearInterpolationVariableStep::LinearInterpolationVariableStep(const std::vector<double>& x, const std::vector<double>& y) : pimpl(new LinearInterpolationVariableStepImpl(x,y))
{

}

double LinearInterpolationVariableStep::f(const double x0)
{
    set_computed_value(x0);
    return pimpl->get_val();
}

double LinearInterpolationVariableStep::df(const double x0)
{
    set_computed_value(x0);
    return pimpl->get_derivative();
}

double LinearInterpolationVariableStep::d2f(const double x0)
{
    set_computed_value(x0);
    return 0;
}

void LinearInterpolationVariableStep::set_computed_value(const double& x0)
{
    pimpl->set_computed_value(x0);
}
