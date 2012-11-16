/*
 * NaturalSpline.cpp
 *
 * \date 1 ao�t 2012, 09:37:58
 *  \author cec
 */

#include "NaturalSplines.hpp"

NaturalSplines::NaturalSplines() : Splines()
{
	M = (h != 0) ? compute_second_derivative() : std::vector<double>(2,0);
}

NaturalSplines::NaturalSplines(const double& xmin_, const double& xmax_, const std::vector<double>& y) : Splines(xmin_, xmax_,y)
{
	M = (h != 0) ? compute_second_derivative() : std::vector<double>(2,0);
}


double NaturalSplines::get_endpoint_value() const
{
	return 4;
}
