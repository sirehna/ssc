/*
 * Splines.cpp
 *
 * \date 8 juin 2012, 17:14:15
 *  \author cec
 */

#include "Splines.hpp"
typedef long int integer;
typedef double doublereal;

#include "SplinesException.hpp"

extern "C"
{
    int dgtsv_(integer *n, integer *nrhs, doublereal *dl,
    	doublereal *d__, doublereal *du, doublereal *b, integer *ldb, integer
    	*info);
}

#include <cmath>
#include <cstdio>
#include "VectorOfEquallySpacedNumbers.hpp"



Splines::Splines() :
				M(std::vector<double>()),
				h(0),
				n(0),
				x_xi(0),
				a(0),
				b(0),
				c(0),
				d(0)
{
}

Splines::Splines(const double& xmin_, const double& xmax_, const std::vector<double>& y) :
        Interpolator(xmin_,xmax_,y),
		M(std::vector<double>()),
		h(VectorOfEquallySpacedNumbers(xmin_,xmax_,y.size()).get_delta()),
		n(y.size()),
		x_xi(0),
		a(0),
		b(0),
		c(0),
		d(0)
{
    if (n==0)
    {
        THROW(__PRETTY_FUNCTION__, SplinesException, "There needs to be at least one point to define the spline (y vector is empty)");
    }
}

void Splines::update_coefficients_if_necessary(const double& x0)
{
	if (n>1)
	{
	    auto coeff = compute_cubic_coeff_for_x0(x0, x_xi);
	    a = coeff.a;
        b = coeff.b;
        c = coeff.c;
        d = coeff.d;
	}

}

CubicCoefficients Splines::compute_cubic_coeff_for_x0(const double& x0, double& xxi) const
{
    const size_t idx = compute_interval_index(x0);
    const double xi = xmin + (xmax-xmin)*double(idx)/double(n-1);
    xxi = x0-xi;
    return get_cubic_coefficients(M.at(idx), M.at(idx+1), y.at(idx),y.at(idx+1));
}

double Splines::get_f() const
{
    return (n==1) ? y.back() : d+x_xi*(c+x_xi*(b+x_xi*a));
}

double Splines::get_df(const size_t derivative_order) const
{
    if (derivative_order==0) return get_f();
    if (derivative_order==1) return (n==1) ? 0 : c+x_xi*(2*b+x_xi*3*a);
    if (derivative_order==2) return (n==1) ? 0 : 2*b+x_xi*6*a;
                             return 0;
}


std::vector<ParabolicCoefficients> Splines::get_parabolic_coefficients() const
{
    std::vector<ParabolicCoefficients> ret;
    for (size_t i = 0 ; i < n-1 ; ++i)
    {
        double x_xi;
        auto coeff = compute_cubic_coeff_for_x0(xmin+(i+0.5)*h, x_xi);
        ret.push_back(ParabolicCoefficients(3*coeff.a,2*coeff.b,coeff.c));
    }
    return ret;
}

std::vector<double> Splines::compute_second_derivative() const
{
	if (n==2) return {0,0};
	if (n==3) return {0,3./2./h/h*(y[0]-2.*y[1]+y[2]),0};
	integer *n_ = new integer;
	integer *nrhs = new integer;
	*n_ = n-2;
	*nrhs = 1;
	doublereal *dl = new doublereal[*n_];
	doublereal *d__ = new doublereal[*n_+2];
	doublereal *du = new doublereal[*n_];
	doublereal *b = new doublereal[*n_+2];
	integer *ldb = new integer;
	integer *info = new integer;
	*ldb = *n_;
	d__[0] = get_endpoint_value();
	d__[*n_+1] = get_endpoint_value();
	b[0] = 0;
	for (int i = 1 ; i <= *n_ ; ++i)
	{
		dl[i-1] = 1;
		du[i-1] = 1;
		d__[i] = 4;
		b[i] = 6./h/h*(y[i-1]-2.*y[i]+y[i+1]);
	}
	b[*n_+1] = 0;
	dgtsv_(n_, nrhs, dl, d__, du, b+1, ldb, info);
	const std::vector<double> ret(b,b+*n_+2);
	delete n_;
	delete nrhs;
	delete [] dl;
	delete [] d__;
	delete [] du;
	delete [] b;
	delete info;
    delete ldb;
	return ret;
}

size_t Splines::compute_interval_index(const double& x0) const
{
    const size_t idx = floor((x0-xmin)/(xmax-xmin)*(n-1));
    return std::min(idx,n-2);
}

CubicCoefficients Splines::get_cubic_coefficients(const double& M1, const double& M2, const double& y1, const double& y2) const
{
    const double a_ = (h!=0) ?(M2-M1)/(6.*h) : 0;
    const double b_ = M1/2.;
    const double c_ = (h!=0) ? (y2-y1)/h - (M2+2.*M1)*h/6. : 0;
    const double d_ = y1;
    return CubicCoefficients(a_,b_,c_,d_);
}

