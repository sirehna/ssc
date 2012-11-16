/*
 * Splines.cpp
 *
 * \date 8 juin 2012, 17:14:15
 *  \author cec
 */

#include "Splines.hpp"
typedef long int integer;
typedef double doublereal;

#define min(a,b) a>b?b:a
#define max(a,b) a<b?b:a

extern "C"
{
    int dgtsv_(integer *n, integer *nrhs, doublereal *dl,
    	doublereal *d__, doublereal *du, doublereal *b, integer *ldb, integer
    	*info);
}

#include <math.h>
#include <stdio.h>
#include "test_macros.hpp"
#include "VectorOfEquallySpacedNumbers.hpp"



Splines::Splines() :
				M(std::vector<double>()),
				h(0),
				xmin(0),
				xmax(0),
				n(0),
				y_(std::vector<double>()),
				x_xi(0),
				a(0),
				b(0),
				c(0),
				d(0)
{
}

Splines::Splines(const double& xmin_, const double& xmax_, const std::vector<double>& y) :
		M(std::vector<double>()),
		h(VectorOfEquallySpacedNumbers(xmin_,xmax_,y.size()).get_delta()),
		xmin(xmin_),
		xmax(xmax_),
		n(y.size()),
		y_(y),
		x_xi(0),
		a(0),
		b(0),
		c(0),
		d(0)
{
}

void Splines::set_computed_value(const double& x0)
{
	if (n>1)
	{
		const size_t idx = compute_interval_index(x0);
		const double xi = xmin + (xmax-xmin)*double(idx)/double(n-1);
		x_xi = x0-xi;
		update_spline_coefficients(M.at(idx), M.at(idx+1), y_.at(idx),y_.at(idx+1));
	}
}

double Splines::f() const
{
    if (n==1) return y_.back();
	return d+x_xi*(c+x_xi*(b+x_xi*a));
}

double Splines::df() const
{
    if (n==1) return 0;
	return c+x_xi*(2*b+x_xi*3*a);
}

double Splines::d2f() const
{
    if (n==1) return 0;
	return 2*b+x_xi*6*a;
}

std::vector<double> Splines::compute_second_derivative() const
{
	if (y_.size()==2) return {0,0};
	if (y_.size()==3) return {0,3./2./h/h*(y_[0]-2.*y_[1]+y_[2]),0};
	integer *n = new integer;
	integer *nrhs = new integer;
	*n = y_.size()-2;
	*nrhs = 1;
	doublereal *dl = new doublereal[*n];
	doublereal *d__ = new doublereal[*n+2];
	doublereal *du = new doublereal[*n];
	doublereal *b = new doublereal[*n+2];
	integer *ldb = new integer;
	integer *info = new integer;
	*ldb = *n;
	d__[0] = get_endpoint_value();
	d__[*n+1] = get_endpoint_value();
	b[0] = 0;
	for (int i = 1 ; i <= *n ; ++i)
	{
		dl[i-1] = 1;
		du[i-1] = 1;
		d__[i] = 4;
		b[i] = 6./h/h*(y_[i-1]-2.*y_[i]+y_[i+1]);
	}
	b[*n+1] = 0;
	dgtsv_(n, nrhs, dl, d__, du, b+1, ldb, info);
	const std::vector<double> ret(b,b+*n+2);
	delete n;
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
    return min(idx,n-2);
}

void Splines::update_spline_coefficients(const double& M1, const double& M2, const double& y1, const double& y2)
{
	a = (h!=0) ?(M2-M1)/(6.*h) : 0;
	b = M1/2.;
	c = (h!=0) ? (y2-y1)/h - (M2+2.*M1)*h/6. : 0;
	d = y1;
}
