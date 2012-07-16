#include "f2c.h"
extern "C" int dgtsv_(integer *n, integer *nrhs, doublereal *dl, 
	doublereal *d__, doublereal *du, doublereal *b, integer *ldb, integer 
	*info);

#include <vector>
#include <math.h>
#include <stdio.h>

std::vector<double> compute_spline_coefficients(const std::vector<double>& y, const double& h)
{
	if (y.empty())  return std::vector<double>();
	if (y.size()==1) return {0};
	if (y.size()==2) return {0,0};
	if (y.size()==3) return {0,3./2./h/h*(y[0]-2.*y[1]+y[2]),0};
	integer *n = new integer;
	integer *nrhs = new integer;
	*n = y.size()-2;
	*nrhs = 1;
	doublereal *dl = new doublereal[*n-1];
	doublereal *d__ = new doublereal[*n];
	doublereal *du = new doublereal[*n-1];
	doublereal *b = new doublereal[*n+2];
	integer *ldb = new integer;
	integer *info = new integer;
	*ldb = *n;
	const doublereal natural_spline = 4;
	const doublereal parabolic_runout_spline = 5;
	const doublereal cubic_runout_spline = 6;
	if (natural_spline+parabolic_runout_spline+cubic_runout_spline) {}
	d__[0] = natural_spline;
	d__[*n+1] = natural_spline;
	b[0] = 0;
	for (size_t i = 1 ; i <= *n ; ++i)
	{
		dl[i-1] = 1;
		du[i-1] = 1;
		d__[i] = 4;
		b[i] = 6./h/h*(y[i-1]-2.*y[i]+y[i+1]);
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
	return ret;
}

double check_x_intervals(const std::vector<double>& x)
{
	double ret = 0;
	if (x.size() >= 2) ret = x.at(1) - x.at(0);
	for (size_t i = 1 ; i < x.size()-1 ; ++i)
	{
		if (x.at(i+1)-x.at(i) != ret) return 0;
	}
	return ret;
}

size_t compute_interval_index(const double& xmin, const double& x, const double& xmax, const size_t& n)
{
	if (x==xmax) return n-2;
	return floor((x-xmin)/(xmax-xmin)*(n-1));
}

double compute_spline_value(const double& x_xi, const double& M1, const double& M2, const double& y1, const double& y2, const double& h)
{
	const double a = (M2-M1)/(6.*h);
	const double b = M1/2.;
	const double c = (y2-y1)/h - (M2+2.*M1)*h/6.;
	const double d = y1;
	return d+x_xi*(c+x_xi*(b+x_xi*a));
}

int main (int argc, char *argv[])
{
	const std::vector<double> x = {0,3,6,9};
	const std::vector<double> y = {0,9,36,81};
	const double dx = check_x_intervals(x);
	//printf("dx = %f\n", dx);
	std::vector<double> xx;
	std::vector<double> yy;
	if (dx)
	{
		const std::vector<double> M = compute_spline_coefficients(y,dx);
		//printf("M.size() = %i\n", M.size());
		const double xmin = x.front();
		const double xmax = x.back();
		const size_t n = x.size();
		const size_t nb_of_values = 10000000;
		for (size_t j = 0 ; j < nb_of_values ; ++j)
		{
			const double x0 = xmin+(xmax-xmin)*j/(nb_of_values-1);
			const size_t idx = compute_interval_index(xmin, x0, xmax, n);
			//printf("x0=%f\n",x0);
			//printf("idx=%i\n",idx);
			//printf("in file %s, line %i: x.at(idx) = %f\n", __FILE__, __LINE__,x.at(idx));
			//printf("in file %s, line %i: M.at(idx) = %f\n", __FILE__, __LINE__,M.at(idx));
			//printf("in file %s, line %i: M.at(idxi+1) = %f\n", __FILE__, __LINE__,M.at(idx+1));
			//printf("in file %s, line %i: y.at(idx) = %f\n", __FILE__, __LINE__,y.at(idx));
			//printf("in file %s, line %i: y.at(idx+1) = %f\n", __FILE__, __LINE__,y.at(idx+1));
			//printf("in file %s, line %i\n", __FILE__, __LINE__);
			double y0 = compute_spline_value(x0-x.at(idx),M.at(idx),M.at(idx+1),y.at(idx),y.at(idx+1), dx);
			xx.push_back(x0);
			yy.push_back(y0);
		}
		//printf("x=[%f,",xx.at(0));
		for (size_t i = 1 ; i < xx.size()-1 ; ++i)
		{
			////printf("%f,", xx.at(i));
		}
		//printf("%f]\n",xx.back());
		//printf("y=[%f,",yy.at(0));
		for (size_t i = 1 ; i < yy.size()-1 ; ++i)
		{
			////printf("%f,", yy.at(i));
		}
		//printf("%f]\n",yy.back());
		

		
	}
	return 0;
}