/*
 * Integrate.cpp
 *
 * \date 23 avr. 2013, 09:47:15
 *  \author cec
 */

#include "Integrate.hpp"
#include <vector>
#include <limits>       // std::numeric_limits
#include <cmath>
#include <algorithm>    // std::min

/*
 * The abscissae and weights are given for the interval (-1,1). Because of
 * symmetry only the positive abscissae and their corresponding weights are
 * given.
 * Gauss quadrature weights and Kronrod quadrature abscissae and weights as
 * evaluated with 80 decimal digit arithmetic by L. W. Fullerton, Bell Labs,
 * Nov. 1981.
 */
static const std::vector<double> weights_of_10_point_gauss_rule = {0.066671344308688137593568809893332,
                                                                     0.149451349150580593145776339657697,
                                                                     0.219086362515982043995534934228163,
                                                                     0.269266719309996355091226921569469,
                                                                     0.295524224714752870173892994651338};
static const std::vector<double> abscissae_21_point_kronrod_rule = {0.995657163025808080735527280689003,
                                                                    0.973906528517171720077964012084452,
                                                                    0.930157491355708226001207180059508,
                                                                    0.865063366688984510732096688423493,
                                                                    0.780817726586416897063717578345042,
                                                                    0.679409568299024406234327365114874,
                                                                    0.562757134668604683339000099272694,
                                                                    0.433395394129247190799265943165784,
                                                                    0.294392862701460198131126603103866,
                                                                    0.148874338981631210884826001129720,
                                                                    0.000000000000000000000000000000000};
static const std::vector<double> weights_of_21_point_kronrod_rule = {0.011694638867371874278064396062192,
                                                                     0.032558162307964727478818972459390,
                                                                     0.054755896574351996031381300244580,
                                                                     0.075039674810919952767043140916190,
                                                                     0.093125454583697605535065465083366,
                                                                     0.109387158802297641899210590325805,
                                                                     0.123491976262065851077958109831074,
                                                                     0.134709217311473325928054001771707,
                                                                     0.142775938577060080797094273138717,
                                                                     0.147739104901338491374841515972068,
                                                                     0.149445554002916905664936468389821};

struct Result
{
        Result() : result(0), error(0), nb_of_function_evaluations(0), error_code(0)
        {

        }

        double result;
        double error;
        size_t nb_of_function_evaluations;
        int error_code;
};

struct GK21_Result
{
        double integral_approximation;
        double estimate_of_modulus_of_absolute_error;
        double approximation_of_integral_of_abs_f;
        double approximation_of_average_error;
};

struct KronrodData
{
        KronrodData() : left_endpoints(std::vector<double>()),
                        right_endpoints(std::vector<double>()),
                        integral_approximation(std::vector<double>()),
                        error_estimate(std::vector<double>()),
                        index_of_decreasingly_sorted_error(std::vector<size_t>()),
                        nb_of_subintervals(0),
                        nb_of_function_evaluations(0)
        {

        }
    std::vector<double> left_endpoints;
    std::vector<double> right_endpoints;
    std::vector<double> integral_approximation;
    std::vector<double> error_estimate;
    std::vector<size_t> index_of_decreasingly_sorted_error;
    size_t nb_of_subintervals;
    size_t nb_of_function_evaluations;
};


class Integrate::IntegrateImpl
{
    public:
        IntegrateImpl(const Function& f_) : f(f_)
        {

        }

        Result integrate(const double& a, const double& b, const double& absolute_tolerance, const double& relative_tolerance) const
        {
            KronrodData kd;


          kd.left_endpoints.push_back(a);
          kd.right_endpoints.push_back(a);
          kd.integral_approximation.push_back(0);
          kd.error_estimate.push_back(0);
          if ((absolute_tolerance<=0) && (relative_tolerance< 1E-28))
          {
              THROW(__PRETTY_FUNCTION__, IntegrateException, "Invalid tolerances");
          }
          const double underflow = std::numeric_limits<double>::min();
          const double overflow = std::numeric_limits<double>::max();

          GK21_Result res = gauss_kronrod_21_points(a,b);




        }

        GK21_Result gauss_kronrod_21_points(const double& a, const double& b) const
        {
            const double epsilon = scalbn(std::numeric_limits<double>::epsilon,1);
            const double underflow = std::numeric_limits<double>::min();
            const double midpoint = (a+b)/2.;
            const double half_length = (b-a)/2.;
            const double dhlgth = fabs(half_length);
            double integral_using_10_point_gauss = 0;
            double fc = f(midpoint);
            double integral_using_21_point_kronrod = fc*weights_of_21_point_kronrod_rule[10];
            GK21_Result ret;
            ret.approximation_of_integral_of_abs_f = fabs(integral_using_21_point_kronrod);
            std::vector<double> fv1(10,0), fv2(10,0);
            for (size_t j = 0 ; j < 5 ; ++j)
            {
                const size_t jtw = 2*j+1;
                const double x = half_length*abscissae_21_point_kronrod_rule[jtw];
                const double fval1 = f(midpoint-x);
                const double fval2 = f(midpoint+x);
                fv1[jtw] = fval1;
                fv2[jtw] = fval2;
                const double fsum = fval1+fval2;
                integral_using_10_point_gauss += weights_of_10_point_gauss_rule[j]*fsum;
                integral_using_21_point_kronrod += weights_of_21_point_kronrod_rule[jtw]*fsum;
                ret.approximation_of_integral_of_abs_f += weights_of_21_point_kronrod_rule[jtw]*(fabs(fval1)+fabs(fval2));
            }
            for (size_t j = 0 ; j < 5 ; ++j)
            {
                const size_t jtwm1 = 2*j;
                const double x = half_length*abscissae_21_point_kronrod_rule[jtwm1];
                const double fval1 = f(midpoint-x);
                const double fval2 = f(midpoint+x);
                fv1[jtwm1] = fval1;
                fv2[jtwm1] = fval2;
                const double fsum = fval1+fval2;
                integral_using_21_point_kronrod = integral_using_21_point_kronrod+weights_of_21_point_kronrod_rule[jtwm1]*fsum;
                ret.approximation_of_integral_of_abs_f += weights_of_21_point_kronrod_rule[jtwm1]*(fabs(fval1)+fabs(fval2));
            }
            const double mean_value_approximation = integral_using_21_point_kronrod/2.;
            ret.approximation_of_average_error = weights_of_21_point_kronrod_rule[10]*fabs(fc-mean_value_approximation);
            for (size_t j = 0 ; j < 10 ; ++j)
            {
                ret.approximation_of_average_error += weights_of_21_point_kronrod_rule[j]*(fabs(fv1[j]-mean_value_approximation)+fabs(fv2[j]-mean_value_approximation));
            }
            ret.integral_approximation = integral_using_21_point_kronrod*half_length;
            ret.approximation_of_integral_of_abs_f *= dhlgth;
            ret.approximation_of_average_error *= dhlgth;
            ret.estimate_of_modulus_of_absolute_error = fabs((integral_using_21_point_kronrod-integral_using_10_point_gauss)*half_length);
            if ((ret.approximation_of_average_error != 0) && (ret.estimate_of_modulus_of_absolute_error!=0))
            {
                ret.estimate_of_modulus_of_absolute_error = ret.approximation_of_average_error*std::min(1,pow(2e2*ret.estimate_of_modulus_of_absolute_error/ret.approximation_of_average_error,1.5));
            }
            if ((ret.approximation_of_integral_of_abs_f>underflow/(50*epsilon)))
            {
                ret.estimate_of_modulus_of_absolute_error = std::max((epsilon*50)*ret.approximation_of_integral_of_abs_f,ret.estimate_of_modulus_of_absolute_error);
            }
            return ret;
        }

    private:
        Function f;
};

Integrate::Integrate(const Function& f) : pimpl(new IntegrateImpl(f))
{

}

double Integrate::integrate(const double& a, const double& b) const
{
    return pimpl->integrate(a,b,1,1).result;
}

